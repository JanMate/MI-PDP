//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_FIRSTTILE_H
#define MI_PDP_FIRSTTILE_H


#include "Tile.h"

class FirstTile : public Tile {
private:
    Direction mDirection;
public:
    FirstTile(int length, Position *inception, Direction direction, int value);

    ~FirstTile() { }

    ObjectType getType() override;

    list<Position> getCells() override;

    Direction getDirection() override;
};


#endif //MI_PDP_FIRSTTILE_H
