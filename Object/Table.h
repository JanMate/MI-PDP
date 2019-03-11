//
// Created by Jan Matějka on 2019-03-08.
//

#ifndef MI_PDP_TABLE_H
#define MI_PDP_TABLE_H


#include "Cell.h"

class Table {
private:
    Cell **mCells;
    int mHeight;
    int mWidth;
public:
    Table(const int height, const int width, Position ***positions);

    Table(const Table& table);

    ~Table();

    Cell& getCell(const int i, const int j);

    void setCell(const int i, const int j, Tile *tile);

    bool isAvailable(const int i, const int j);

    bool situateTile(Tile* tile);

    void print();
};


#endif //MI_PDP_TABLE_H
