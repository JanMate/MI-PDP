//
// Created by Jan Matějka on 2019-03-08.
//

#ifndef MI_PDP_DISABLEDTILE_H
#define MI_PDP_DISABLEDTILE_H


#include <string>
#include "Tile.h"

class DisabledTile: public Tile {
private:

public:
    DisabledTile(int length, Position position, int value);

    ~DisabledTile() { }

    int printX() { return mInception.x; }

    int printY() { return mInception.y; }

    ObjectType getType() override;

    list<Position> getCells() override;

    Direction getDirection() override;
};


#endif //MI_PDP_DISABLEDTILE_H
