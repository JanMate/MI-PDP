//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_SIMPLETILE_H
#define MI_PDP_SIMPLETILE_H


#include "../HelpfulObject/Position.h"
#include "../HelpfulObject/Direction.h"
#include "Tile.h"

class SimpleTile: public Tile {
private:

public:
    SimpleTile(int length, const int x, const int y, int value);

    ~SimpleTile() { }

    ObjectType getType() override;

    Direction getDirection() override;
};


#endif //MI_PDP_SIMPLETILE_H
