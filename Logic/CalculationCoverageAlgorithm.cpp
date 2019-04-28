//
// Created by Jan Matějka on 2019-03-07.
//

#include "CalculationCoverageAlgorithm.h"

CalculationCoverageAlgorithm::CalculationCoverageAlgorithm(const Factory &factory)
                                                :factory(factory), initTable(factory.createTable()),
                                                 bestTable(*(factory.createTable())) { }

CalculationCoverageAlgorithm::~CalculationCoverageAlgorithm() {
    delete initTable;
}

void CalculationCoverageAlgorithm::fillDisabledTiles(const list<DisabledTile *> &disabledTiles) {
    for (DisabledTile* tile : disabledTiles){
        initTable->setCell(tile->getX(), tile->getY(), ObjectType::Disabled);
        initTable->decrementFreeCell();
    }
    upperBound = eval_poi(initTable->getCountOfEmptyCells());
}

void CalculationCoverageAlgorithm::process(int &argc, char **argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    double startTime = MPI_Wtime();

    // An algorithm starts here
    int i = 0, j = 0;
    bool end = false;
    while (!initTable->isAvailable(i, j)){
        end = increment(&i, &j, 1);
        if (end){
            break;
        }
    }
    if (end)
        return;

    generateStates(i, j);

    int buffer[LENGTH];
    int k = 0, l;
    if (rank == 0){ // master process
        for (k = 0, l = 1; k < states.size() - 1 && l < processes; ++k, ++l){
            // i,j,k
            buffer[0] = i;
            buffer[1] = j;
            buffer[2] = k;
            MPI_Send (buffer, LENGTH, MPI_INT, l, tag, MPI_COMM_WORLD);
        }
        int workingProcesses = processes - 1;
        while(workingProcesses){
            MPI_Recv(buffer, LENGTH, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            i = buffer[0];
            j = buffer[1];
            //k = buffer[2];
            bestValue = buffer[3];
            loadBestTable(buffer);

            int destination = status.MPI_SOURCE;
            if(buffer[0] == TO_END){
                i = -1;
                MPI_Send(&i, LENGTH, MPI_INT, destination, tag, MPI_COMM_WORLD);
                workingProcesses--;
            } else {
                //poslat dosud nejlepsi dosazene reseni
                if (k++ < states.size() - 1) {
                    buffer[0] = i;
                    buffer[1] = j;
                    buffer[2] = k;
                    MPI_Send(buffer, LENGTH, MPI_INT, destination, tag, MPI_COMM_WORLD);
                } else {
                    buffer[0] = -1;
                    MPI_Send(buffer, LENGTH, MPI_INT, destination, tag, MPI_COMM_WORLD);
                }
            }
        }

        bestTable.print();
        cout << "Best value: " << bestValue << endl << endl;

    } else { // slave process
        while (!END){
            MPI_Recv(buffer, LENGTH, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            i = buffer[0];
            j = buffer[1];
            k = buffer[2];
            if (i == TO_END){
                buffer[0] = -1;
                MPI_Send (buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                END = true;
            } else {
                if (argv[2] != nullptr) {
                    omp_set_num_threads(atoi(argv[2]));
                }
                #pragma omp parallel
                #pragma omp task
                iterate(states[k].getTable(), factory.createFirstTile(states[k].getI(), states[k].getJ(), Direction::Horizontal), states[k].getI(), states[k].getJ(), states[k].getTempValue(), states[k].getLocalId());
                #pragma omp task
                iterate(states[k].getTable(), factory.createFirstTile(states[k].getI(), states[k].getJ(), Direction::Vertical), states[k].getI(), states[k].getJ(), states[k].getTempValue(), states[k].getLocalId());
                #pragma omp task
                iterate(states[k].getTable(), factory.createSecondTile(states[k].getI(), states[k].getJ(), Direction::Horizontal), states[k].getI(), states[k].getJ(), states[k].getTempValue(), states[k].getLocalId());
                #pragma omp task
                iterate(states[k].getTable(), factory.createSecondTile(states[k].getI(), states[k].getJ(), Direction::Vertical), states[k].getI(), states[k].getJ(), states[k].getTempValue(), states[k].getLocalId());
                #pragma omp task
                iterate(states[k].getTable(), factory.createSimpleTile(states[k].getI(), states[k].getJ()), states[k].getI(), states[k].getJ(), states[k].getTempValue(), states[k].getLocalId());
                buffer[3] = bestValue;
                fillBestTable(buffer);
                MPI_Send (buffer, LENGTH, MPI_INT, 0, tag, MPI_COMM_WORLD);
            }
        }
    }

    double endTime = MPI_Wtime();

    if(!rank) {
        cout << "Elapsed time : " << (endTime - startTime) << endl;
    }

    MPI_Finalize();
}

void CalculationCoverageAlgorithm::iterate(Table table, Tile *tile, int i, int j, int tempValue, int localId) {
    bool end;
    if (table.situateTile(tile, localId)) {
        tempValue += tile->getValue();
        end = increment(&i, &j, (tile->getDirection() == Direction::Vertical ? 1 : tile->getLength()));
        while (!table.isAvailable(i, j) && !end){
            end = increment(&i, &j, 1);
            if (end){
                break;
            }
        }
        localId++;
        delete tile;

        if (tempValue + eval_poi(table.getCountOfEmptyCells()) <= bestValue) {
            return;
        }
    } else {
        delete tile;
        return;
    }

    if (end) {
        int currentValue = tempValue + (table.getCountOfEmptyCells() * factory.getSimpleTypeValue());
        if (bestValue < currentValue){
            # pragma omp critical
            {
                if (bestValue < currentValue) {
                    bestValue = currentValue;
                    bestTable = Table(table);

                }
            };
        }
        if (upperBound == bestValue){
            return;
        }
        return;
    }

    #pragma omp task
    iterate(table, factory.createFirstTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    #pragma omp task
    iterate(table, factory.createFirstTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    #pragma omp task
    iterate(table, factory.createSecondTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    #pragma omp task
    iterate(table, factory.createSecondTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    #pragma omp task
    iterate(table, factory.createSimpleTile(i, j), i, j, tempValue, localId);
}

void CalculationCoverageAlgorithm::generateStates(int i, int j) {

    iterateState(*initTable, factory.createFirstTile(i, j, Direction::Horizontal), i, j, 0, id, 1);
    iterateState(*initTable, factory.createFirstTile(i, j, Direction::Vertical), i, j, 0, id, 1);
    iterateState(*initTable, factory.createSecondTile(i, j, Direction::Horizontal), i, j, 0, id, 1);
    iterateState(*initTable, factory.createSecondTile(i, j, Direction::Vertical), i, j, 0, id, 1);
    iterateState(*initTable, factory.createSimpleTile(i, j), i, j, 0, id, 1);

}

void CalculationCoverageAlgorithm::iterateState(Table table, Tile *tile, int i, int j, int tempValue, int localId,
                                                int level) {
    if (level == generatedDepth){
        states.emplace_back(table, i, j, tempValue, localId);
        delete tile;
        return;
    }

    if (table.situateTile(tile, localId)){
        tempValue += tile->getValue();
        increment(&i, &j, (tile->getDirection() == Direction::Vertical ? 1 : tile->getLength()));
        while (!table.isAvailable(i, j)){
            increment(&i, &j, 1);
        }
        localId++;
        delete tile;
    } else {
        delete tile;
        return;
    }

    iterateState(table, factory.createFirstTile(i, j, Direction::Horizontal), i, j, tempValue, localId, level + 1);
    iterateState(table, factory.createFirstTile(i, j, Direction::Vertical), i, j, tempValue, localId, level + 1);
    iterateState(table, factory.createSecondTile(i, j, Direction::Horizontal), i, j, tempValue, localId, level + 1);
    iterateState(table, factory.createSecondTile(i, j, Direction::Vertical), i, j, tempValue, localId, level + 1);
    iterateState(table, factory.createSimpleTile(i, j), i, j, tempValue, localId, level + 1);

}

bool CalculationCoverageAlgorithm::increment(int *i, int *j, int count) {
    if (*j + count >= factory.getWidth()) {
        *i += ((*j + count + 1) / factory.getWidth());
        *j = ((*j + count) % factory.getWidth());
    } else {
        *j += count;
    }
    return *i >= factory.getHeight();
}

int CalculationCoverageAlgorithm::eval_poi(int number) {
    // vraci maximalni cenu pro "number" nevyresenych policek
    // returns the maximal price for the "number" of unsolved squares
    int i,x;
    int max=factory.getSecondTypeValue()*(number/factory.getSecondTypeLength());
    int zb=number%factory.getSecondTypeLength();
    max+=factory.getFirstTypeValue()*(zb/factory.getFirstTypeLength());
    zb=zb%factory.getFirstTypeLength();
    max+=zb*factory.getSimpleTypeValue();
    for(i=0;i<(number/factory.getSecondTypeLength());i++)
    {
        x=factory.getSecondTypeValue()*i;
        zb=number-i*factory.getSecondTypeLength();
        x+=factory.getFirstTypeValue()*(zb/factory.getFirstTypeLength());
        zb=zb%factory.getFirstTypeLength();
        x+=zb*factory.getSimpleTypeValue();
        if (x>max) max=x;
    }
    return max;
}

void CalculationCoverageAlgorithm::loadBestTable(int *buffer) {
    bestTable.fromArray(buffer);
}

void CalculationCoverageAlgorithm::fillBestTable(int *buffer) {
    bestTable.toArray(buffer);
}

