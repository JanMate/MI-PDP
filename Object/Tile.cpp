//
// Created by Jan Matějka on 2019-03-07.
//

#include "Tile.h"

Tile::Tile(int length, Position *position, int value) :
        mLength(length), mInception(position), mValue(value) {}

list <Position> Tile::getCells() {
    return list<Position>();
}
