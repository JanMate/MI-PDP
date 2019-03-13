//
// Created by Jan Matějka on 2019-03-07.
//

#include "SimpleTile.h"

SimpleTile::SimpleTile(int length, Position position, int value)
                : Tile(length, position, value){

}

ObjectType SimpleTile::getType() {
    return ObjectType::Simple;
}

list<Position> SimpleTile::getCells() {
    list<Position> positions = list<Position>();
    positions.emplace_back(mInception.x, mInception.y);
    return positions;
}

Direction SimpleTile::getDirection() {
    return Horizontal;
}
