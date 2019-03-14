//
// Created by Jan Matějka on 2019-03-07.
//

#include "CalculationCoverageAlgorithm.h"

CalculationCoverageAlgorithm::CalculationCoverageAlgorithm(const Factory &factory)
                                                :mFactory(factory), mTable(factory.createTable()),
                                                 bestTable(*(factory.createTable())) { }

CalculationCoverageAlgorithm::~CalculationCoverageAlgorithm() {
    delete mTable;
}

void CalculationCoverageAlgorithm::fillDisabledTiles(const list<DisabledTile *> &disabledTiles) {
    for (DisabledTile* tile : disabledTiles){
        mTable->setCell(tile->getX(), tile->getY(), ObjectType::Disabled);
        mTable->decrementFreeCell();
    }
    upperBound = eval_poi(mTable->getCountOfEmptyCells());
}

void CalculationCoverageAlgorithm::process() {
    int i = 0, j = 0;
    bool end = false;
    while (!mTable->isAvailable(i, j)){
        end = increment(&i, &j, 1);
        if (end){
            break;
        }
    }
    if (end)
        return;

    iterate(*mTable, mFactory.createFirstTile(i, j, Direction::Horizontal), i, j, 0, id);
    iterate(*mTable, mFactory.createFirstTile(i, j, Direction::Vertical), i, j, 0, id);
    iterate(*mTable, mFactory.createSecondTile(i, j, Direction::Horizontal), i, j, 0, id);
    iterate(*mTable, mFactory.createSecondTile(i, j, Direction::Vertical), i, j, 0, id);
    iterate(*mTable, mFactory.createSimpleTile(i, j), i, j, 0, id);
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
        int currentValue = tempValue + (table.getCountOfEmptyCells() * -2);
        if (bestValue < currentValue){
            bestValue = currentValue;
            bestTable = Table(table);
        }
        if (upperBound == bestValue){
            return;
        }
        return;
    }

    iterate(table, mFactory.createFirstTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    iterate(table, mFactory.createFirstTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    iterate(table, mFactory.createSecondTile(i, j, Direction::Horizontal), i, j, tempValue, localId);
    iterate(table, mFactory.createSecondTile(i, j, Direction::Vertical), i, j, tempValue, localId);
    iterate(table, mFactory.createSimpleTile(i, j), i, j, tempValue, localId);
}

bool CalculationCoverageAlgorithm::increment(int *i, int *j, int count) {
    if (*j + count >= mFactory.getWidth()) {
        *i += ((*j + count + 1) / mFactory.getWidth());
        *j = ((*j + count) % mFactory.getWidth());
    } else {
        *j += count;
    }
    return *i >= mFactory.getHeight();
}

int CalculationCoverageAlgorithm::eval_poi(int number) {
    // vraci maximalni cenu pro "number" nevyresenych policek
    // returns the maximal price for the "number" of unsolved squares
    int i,x;
    int max=mFactory.getSecondTypeValue()*(number/mFactory.getSecondTypeLength());
    int zb=number%mFactory.getSecondTypeLength();
    max+=mFactory.getFirstTypeValue()*(zb/mFactory.getFirstTypeLength());
    zb=zb%mFactory.getFirstTypeLength();
    max+=zb*mFactory.getSimpleTypeValue();
    for(i=0;i<(number/mFactory.getSecondTypeLength());i++)
    {
        x=mFactory.getSecondTypeValue()*i;
        zb=number-i*mFactory.getSecondTypeLength();
        x+=mFactory.getFirstTypeValue()*(zb/mFactory.getFirstTypeLength());
        zb=zb%mFactory.getFirstTypeLength();
        x+=zb*mFactory.getSimpleTypeValue();
        if (x>max) max=x;
    }
    return max;
}
