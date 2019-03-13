//
// Created by Jan Matějka on 2019-03-08.
//

#ifndef MI_PDP_TABLE_H
#define MI_PDP_TABLE_H


#include <vector>
#include "Tile.h"

using namespace std;

class Table {
private:
    vector<int> mCells;
    int mHeight;
    int mWidth;
    int emptyCells;
    vector<Position> simpleTiles;

public:
    Table() {}

    Table(const int height, const int width);

    Table(const Table& table);

    ~Table();

    int & getCell(const int i, const int j);

    void setCell(const int i, const int j, const int id);

    bool isAvailable(const int i, const int j);

    bool situateTile(Tile* tile, const int id);

    void print();

    int getCountOfEmptyCells();
};


#endif //MI_PDP_TABLE_H
