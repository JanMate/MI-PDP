//
// Created by Jan Matějka on 2019-03-07.
//

#include "FirstTile.h"

FirstTile::FirstTile(int length, const int x, const int y, Direction direction, int value):
                Tile(length, x, y, value), mDirection(direction) { }

ObjectType FirstTile::getType() {
    return ObjectType::First;
}

Direction FirstTile::getDirection() {
    return mDirection;
}
