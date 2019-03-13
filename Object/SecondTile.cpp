//
// Created by Jan Matějka on 2019-03-07.
//

#include "SecondTile.h"

SecondTile::SecondTile(int length, Position position, Direction direction, int value)
                : Tile (length, position, value), mDirection(direction) { }

ObjectType SecondTile::getType() {
    return ObjectType::Second;
}

list<Position> SecondTile::getCells() {
    list<Position> positions = list<Position>();
    for (int i = 0; i < mLength; ++i)
        positions.emplace_back(mInception.x + (mDirection == Direction::Vertical ? i : 0),
                               mInception.y + (mDirection == Direction::Vertical ? 0 : i));
    return positions;
}

Direction SecondTile::getDirection() {
    return mDirection;
}
