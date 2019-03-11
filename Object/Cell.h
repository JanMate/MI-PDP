//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_CELL_H
#define MI_PDP_CELL_H


#include "../HelpfulObject/Position.h"
#include "Tile.h"

class Cell {
private:
    Tile *tile;

public:
    Cell() {}

    Tile *getTile() const;

    void setTile(Tile* tile);

    ObjectType getType() {
        return getTile()->getType();
    }

    char print() { return 'i'; }
};


#endif //MI_PDP_CELL_H
