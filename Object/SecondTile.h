//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_SECONDTILE_H
#define MI_PDP_SECONDTILE_H


#include "../HelpfulObject/Position.h"
#include "../HelpfulObject/Direction.h"
#include "Tile.h"

class SecondTile: public Tile {
private:
    Direction mDirection;
public:
    SecondTile(int length, Position position, Direction direction, int value);

    ~SecondTile() { }

    ObjectType getType() override;

    list<Position> getCells() override;

    Direction getDirection() override;
};


#endif //MI_PDP_SECONDTILE_H
