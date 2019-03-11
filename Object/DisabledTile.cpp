//
// Created by Jan Matějka on 2019-03-08.
//

#include "DisabledTile.h"

DisabledTile::DisabledTile(int length, Position *position, int value) : Tile(length, position, value) {}

ObjectType DisabledTile::getType() {
    return ObjectType::Disabled;
}

list<Position> DisabledTile::getCells() {
    list<Position> positions = list<Position>();
    positions.emplace_back(mInception->x, mInception->y);
    return positions;
}

Direction DisabledTile::getDirection() {
    return Horizontal;
}

