//
// Created by Jan Matějka on 2019-03-07.
//

#include "CalculationCoverageAlgorithm.h"

CalculationCoverageAlgorithm::CalculationCoverageAlgorithm(const Factory &factory)
                                                :mFactory(factory), mTable(factory.createTable()), bestTable() {

}

CalculationCoverageAlgorithm::~CalculationCoverageAlgorithm() {
    delete mTable;
}

void CalculationCoverageAlgorithm::fillDisabledTiles(const list<DisabledTile *> &disabledTiles) {
    for (DisabledTile* tile : disabledTiles){
        mTable->setCell(tile->getPosition().x, tile->getPosition().y, ObjectType::Disabled);
    }
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

//    mTable->print();

    iterate(*mTable, mFactory.createFirstTile(Position(i, j), Direction::Horizontal), i, j, 0, id);
    iterate(*mTable, mFactory.createFirstTile(Position(i, j), Direction::Vertical), i, j, 0, id);
    iterate(*mTable, mFactory.createSecondTile(Position(i, j), Direction::Horizontal), i, j, 0, id);
    iterate(*mTable, mFactory.createSecondTile(Position(i, j), Direction::Vertical), i, j, 0, id);
    iterate(*mTable, mFactory.createSimpleTile(Position(i, j)), i, j, 0, id);
}

void CalculationCoverageAlgorithm::iterate(Table table, Tile *tile, int i, int j, int tempValue, int localId) {
    if (completelyEnd)
        return;

    bool end;

    if (table.situateTile(tile, localId)) {
        tempValue += tile->getValue();
        end = increment(&i, &j, (tile->getDirection() == Direction::Vertical ? 1 : tile->getLength()));
        localId++;
        delete tile;
    } else {
        delete tile;
        return;
    }

//    table.print();

    while (!table.isAvailable(i, j) && !end){
        end = increment(&i, &j, 1);
        if (end){
            break;
        }
    }
    if (end) {
        if (bestValue < tempValue) {
            bestValue = tempValue;
            bestTable = Table(table);
            if (round_value() >= bestValue && eval_poi(table.getCountOfEmptyCells()) <= bestValue)
                completelyEnd = true;
        }
        return;
    }

    iterate(table, mFactory.createFirstTile(Position(i, j), Direction::Horizontal), i, j, tempValue, localId);
    iterate(table, mFactory.createFirstTile(Position(i, j), Direction::Vertical), i, j, tempValue, localId);
    iterate(table, mFactory.createSecondTile(Position(i, j), Direction::Horizontal), i, j, tempValue, localId);
    iterate(table, mFactory.createSecondTile(Position(i, j), Direction::Vertical), i, j, tempValue, localId);
    iterate(table, mFactory.createSimpleTile(Position(i, j)), i, j, tempValue, localId);
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

int CalculationCoverageAlgorithm::round_value() {
    return mFactory.getSimpleTypeValue() * (mFactory.getHeight() * mFactory.getWidth() - mFactory.getDisabledCount());
}


