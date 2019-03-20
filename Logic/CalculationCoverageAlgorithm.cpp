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

void CalculationCoverageAlgorithm::process() {
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

    #pragma omp task
        iterate(*initTable, factory.createFirstTile(i, j, Direction::Horizontal), i, j, 0, id);
    #pragma omp task
        iterate(*initTable, factory.createFirstTile(i, j, Direction::Vertical), i, j, 0, id);
    #pragma omp task
        iterate(*initTable, factory.createSecondTile(i, j, Direction::Horizontal), i, j, 0, id);
    #pragma omp task
        iterate(*initTable, factory.createSecondTile(i, j, Direction::Vertical), i, j, 0, id);
    #pragma omp task
        iterate(*initTable, factory.createSimpleTile(i, j), i, j, 0, id);

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

    #pragma omp task if (i < (factory.getHeight() - 1))
        iterate(table, factory.createFirstTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    #pragma omp task if (i < (factory.getHeight() - 1))
        iterate(table, factory.createFirstTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    #pragma omp task if (i < (factory.getHeight() - 1))
        iterate(table, factory.createSecondTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    #pragma omp task if (i < (factory.getHeight() - 1))
        iterate(table, factory.createSecondTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    #pragma omp task if (i < (factory.getHeight() - 1))
        iterate(table, factory.createSimpleTile(i, j), i, j, tempValue, localId);
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
