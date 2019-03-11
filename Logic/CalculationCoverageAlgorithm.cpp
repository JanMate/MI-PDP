//
// Created by Jan Matějka on 2019-03-07.
//

#include "CalculationCoverageAlgorithm.h"

CalculationCoverageAlgorithm::CalculationCoverageAlgorithm(const Factory &factory)
                                                :mFactory(factory), mPositions(factory.createPositions()),
                                                 mTable(factory.createTable(factory.createPositions())) {

}

CalculationCoverageAlgorithm::~CalculationCoverageAlgorithm() {
    delete mTable;
}

void CalculationCoverageAlgorithm::fillDisabledTiles(const list<DisabledTile *> &disabledTiles) {
    for (DisabledTile* tile : disabledTiles){
        mTable->setCell(tile->getPosition()->x, tile->getPosition()->y, tile);
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

    iterate(*mTable, new FirstTile(mFactory.getFirstTypeLength(), mPositions[i][j], Direction::Horizontal,
                                   mFactory.getFirstTypeValue()), i, j, 0);
    iterate(*mTable, new FirstTile(mFactory.getFirstTypeLength(), mPositions[i][j], Direction::Vertical,
                                   mFactory.getFirstTypeValue()), i, j, 0);
    iterate(*mTable, new SecondTile(mFactory.getSecondTypeLength(), mPositions[i][j], Direction::Horizontal,
                                    mFactory.getSecondTypeValue()), i, j, 0);
    iterate(*mTable, new SecondTile(mFactory.getSecondTypeLength(), mPositions[i][j], Direction::Vertical,
                                    mFactory.getSecondTypeValue()), i, j, 0);
    iterate(*mTable, new SimpleTile(1, mPositions[i][j], mFactory.getSimpleTypeValue()), i, j, 0);
}

void CalculationCoverageAlgorithm::iterate(Table table, Tile *tile, int i, int j, int tempValue) {
    bool end;
    if (table.situateTile(tile)) {
        tempValue += tile->getValue();
        end = increment(&i, &j, (tile->getDirection() == Direction::Vertical ? 1 : tile->getLength()));
    } else {
        return;
    }

    while (!table.isAvailable(i, j) && !end){
        end = increment(&i, &j, 1);
        if (end){
            break;
        }
    }
    if (end) {
        if (maxValue < tempValue)
            maxValue = tempValue;
        return;
    }

    iterate(table, new FirstTile(mFactory.getFirstTypeLength(), mPositions[i][j], Direction::Horizontal,
                                   mFactory.getFirstTypeValue()), i, j, tempValue);
    iterate(table, new FirstTile(mFactory.getFirstTypeLength(), mPositions[i][j], Direction::Vertical,
                                   mFactory.getFirstTypeValue()), i, j, tempValue);
    iterate(table, new SecondTile(mFactory.getSecondTypeLength(), mPositions[i][j], Direction::Horizontal,
                                    mFactory.getSecondTypeValue()), i, j, tempValue);
    iterate(table, new SecondTile(mFactory.getSecondTypeLength(), mPositions[i][j], Direction::Vertical,
                                    mFactory.getSecondTypeValue()), i, j, tempValue);
    iterate(table, new SimpleTile(1, mPositions[i][j], mFactory.getSimpleTypeValue()), i, j, tempValue);
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


