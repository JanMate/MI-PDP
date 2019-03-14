//
// Created by Jan Matějka on 2019-03-08.
//

#include "DisabledTile.h"

DisabledTile::DisabledTile(int length, const int x, const int y, int value) : Tile(length, x, y, value) { }

ObjectType DisabledTile::getType() {
    return ObjectType::Disabled;
}

Direction DisabledTile::getDirection() {
    return Horizontal;
}

