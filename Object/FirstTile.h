//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_FIRSTTILE_H
#define MI_PDP_FIRSTTILE_H


#include "Tile.h"

class FirstTile : public Tile {
private:
    Direction direction;

public:
    FirstTile(int length, const int x, const int y, Direction direction, int value);

    ~FirstTile() override = default;

    ObjectType getType() override;

    Direction getDirection() override;
};


#endif //MI_PDP_FIRSTTILE_H
