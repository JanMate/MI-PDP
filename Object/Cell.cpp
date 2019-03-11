//
// Created by Jan Matějka on 2019-03-07.
//

#include "Cell.h"

void Cell::setTile(Tile *tile) {
    this->tile = tile;
}

Tile *Cell::getTile() const {
    return tile;
}
