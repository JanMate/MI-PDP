//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_TILE_H
#define MI_PDP_TILE_H

#include <list>
#include "../HelpfulObject/Position.h"
#include "../HelpfulObject/Direction.h"
#include "../HelpfulObject/ObjectType.h"

using namespace std;

class Position;

class Tile {
protected:
    int mLength;
    Position mInception;
    int mValue;

public:
    Tile(int length, Position position, int value);

    virtual ~Tile() = default;

    Position getPosition() { return mInception; };

    int getValue() { return mValue; }

    virtual ObjectType getType() { return ObjectType::Empty; }

    virtual list<Position> getCells();

    virtual Direction getDirection() { return Direction::Horizontal; };

    int getLength() { return mLength; }
};


#endif //MI_PDP_TILE_H
