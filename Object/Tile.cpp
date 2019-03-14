//
// Created by Jan Matějka on 2019-03-07.
//

#include "Tile.h"

Tile::Tile(int length, const int x, const int y, int value) :
        length(length), x(x), y(y), value(value) { }

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}
