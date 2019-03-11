//
// Created by Jan Matějka on 2019-03-07.
//

#include "FirstTile.h"

FirstTile::FirstTile(int length, Position *inception, Direction direction, int value):
                Tile(length, inception, value), mDirection(direction) {

}

ObjectType FirstTile::getType() {
    return ObjectType::First;
}

list<Position> FirstTile::getCells() {
    list<Position> positions = list<Position>();
    for (int i = 0; i < mLength; ++i)
        positions.emplace_back(mInception->x + (mDirection == Direction::Vertical ? i : 0),
                               mInception->y + (mDirection == Direction::Vertical ? 0 : i));
    return positions;
}

Direction FirstTile::getDirection() {
    return mDirection;
}
