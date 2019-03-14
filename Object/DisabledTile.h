//
// Created by Jan Matějka on 2019-03-08.
//

#ifndef MI_PDP_DISABLEDTILE_H
#define MI_PDP_DISABLEDTILE_H


#include <string>
#include "Tile.h"

class DisabledTile: public Tile {
public:
    DisabledTile(int length, const int x, const int y, int value);

    ~DisabledTile() { }

    ObjectType getType() override;

    Direction getDirection() override;
};


#endif //MI_PDP_DISABLEDTILE_H
