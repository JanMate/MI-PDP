//
// Created by Jan Matějka on 2019-03-07.
//

#include "SecondTile.h"

SecondTile::SecondTile(int length, const int x, const int y, Direction direction, int value)
                : Tile (length, x, y, value), mDirection(direction) { }

ObjectType SecondTile::getType() {
    return ObjectType::Second;
}

Direction SecondTile::getDirection() {
    return mDirection;
}
