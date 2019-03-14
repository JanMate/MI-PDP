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

class Tile {
protected:
    int mLength;
    int x;
    int y;
    int mValue;

public:
    Tile(int length, const int x, const int y, int value);

    virtual ~Tile() = default;

    int getX() const;

    int getY() const;

    int getValue() { return mValue; }

    virtual ObjectType getType() { return ObjectType::Empty; }

    virtual Direction getDirection() { return Direction::Horizontal; };

    int getLength() { return mLength; }
};


#endif //MI_PDP_TILE_H
