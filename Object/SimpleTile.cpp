//
// Created by Jan Matějka on 2019-03-07.
//

#include "SimpleTile.h"

SimpleTile::SimpleTile(int length, const int x, const int y, int value): Tile(length, x, y, value) { }

ObjectType SimpleTile::getType() {
    return ObjectType::Simple;
}

Direction SimpleTile::getDirection() {
    return Horizontal;
}
