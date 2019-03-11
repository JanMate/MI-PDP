//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_CALCULATIONCOVERAGEALGORITHM_H
#define MI_PDP_CALCULATIONCOVERAGEALGORITHM_H


#include <list>
#include <iostream>
#include "../Object/Cell.h"
#include "../Factory/Factory.h"
#include "../Object/Table.h"

using namespace std;

class CalculationCoverageAlgorithm {
private:
    Table*  mTable;
    int     maxValue = 0;
    Factory mFactory;
    Position*** mPositions;

    void iterate(Table table, Tile *tile, int i, int j, int tempValue);

    bool increment(int *i, int *j, int count);
public:
    CalculationCoverageAlgorithm(const Factory &factory);

    ~CalculationCoverageAlgorithm();

    void process();

    int getMaxValue() { return maxValue; }

    void fillDisabledTiles(const list<DisabledTile*> &disabledTiles);
};


#endif //MI_PDP_CALCULATIONCOVERAGEALGORITHM_H
