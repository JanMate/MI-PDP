//
// Created by Jan Matějka on 2019-04-07.
//

#include "State.h"

State::State(Table table, int i, int j, int tempValue, int localId) : table(table), i(i), j(j),
                                                                             tempValue(tempValue), localId(localId) {}

const Table &State::getTable() const {
    return table;
}

int State::getI() const {
    return i;
}

int State::getJ() const {
    return j;
}

int State::getTempValue() const {
    return tempValue;
}

int State::getLocalId() const {
    return localId;
}
