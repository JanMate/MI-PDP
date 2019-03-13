//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_CALCULATIONCOVERAGEALGORITHM_H
#define MI_PDP_CALCULATIONCOVERAGEALGORITHM_H


#include <list>
#include <iostream>
#include "../Factory/Factory.h"
#include "../Object/Table.h"

using namespace std;

class CalculationCoverageAlgorithm {
private:
    Table*  mTable;
    int     bestValue = INT_MIN;
    Table   bestTable;
    Factory mFactory;
    int id = 1;
    bool completelyEnd = false;

    void iterate(Table table, Tile *tile, int i, int j, int tempValue, int localId);

    bool increment(int *i, int *j, int count);

    int eval_poi(int number);

    int round_value();
public:
    explicit CalculationCoverageAlgorithm(const Factory &factory);

    ~CalculationCoverageAlgorithm();

    void process();

    int getBestValue() { return bestValue; }

    Table getBestTable() { return bestTable; }

    void fillDisabledTiles(const list<DisabledTile *> &disabledTiles);
};


#endif //MI_PDP_CALCULATIONCOVERAGEALGORITHM_H
