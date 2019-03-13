//
// Created by Jan Matějka on 2019-03-07.
//

#include "Tile.h"

Tile::Tile(int length, const int x, const int y, int value) :
        mLength(length), x(x), y(y), mValue(value) {}

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}
