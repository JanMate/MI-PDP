//
// Created by Jan Matějka on 2019-04-07.
//

#ifndef MI_PDP_STATE_H
#define MI_PDP_STATE_H


#include "../Object/Table.h"

class State {
private:
    Table table;
    int i;
    int j;
    int tempValue;
    int localId;
public:
    State() = default;

    State(Table table, int i, int j, int tempValue, int localId);

    ~State();
};


#endif //MI_PDP_STATE_H