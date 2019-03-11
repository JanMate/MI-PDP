//
// Created by Jan Matějka on 2019-03-08.
//

#include <iostream>
#include "Table.h"
#include "SimpleTile.h"

Table::Table(const int height, const int width, Position ***positions) : mHeight(height), mWidth(width) {
    Cell **cells = new Cell*[mHeight];
    for (int i = 0; i < mHeight; ++i){
        cells[i] = new Cell[mWidth];
    }
    mCells = cells;
    for (int i = 0; i < mHeight; ++i){
        for (int j = 0; j < mWidth; ++j){
            mCells[i][j].setTile(new Tile(1, positions[i][j], 0));
        }
    }
}

Table::Table(const Table &table): mHeight(table.mHeight), mWidth(table.mWidth) {
    Cell **cells = new Cell*[mHeight];
    for (int i = 0; i < mHeight; ++i){
        cells[i] = new Cell[mWidth];
    }
    mCells = cells;
    for (int i = 0; i < mHeight; ++i){
        for (int j = 0; j < mWidth; ++j) {
            mCells[i][j].setTile(table.mCells[i][j].getTile());
        }
    }
}

Table::~Table() {
    if (mCells != nullptr){
        for (int i = 0; i < mHeight; ++i){
            for (int j = 0; j < mWidth; ++j) {
//                if (mCells[i][j].getTile() != nullptr)
//                    delete mCells[i][j].getTile();
            }
        }

        for (int i = 0; i < mHeight; ++i){
            delete (mCells[i]);
        }
        delete (mCells);
    }
}

Cell& Table::getCell(const int i, const int j) {
    return mCells[i][j];
}

void Table::setCell(const int i, const int j, Tile *tile) {
    mCells[i][j].setTile(tile);
}

void Table::print() {
    for (int i = 0; i < mHeight; ++i){
        for (int j = 0; j < mWidth; ++j){
            std::cout << mCells[i][j].getType();
        }
        std::cout << std::endl;
    }
}

bool Table::isAvailable(const int i, const int j) {
    return mCells[i][j].getType() == ObjectType::Empty;
}

bool Table::situateTile(Tile *tile) {
    for (Position p : tile->getCells()){
        if (p.x >= mHeight || p.y >= mWidth || !isAvailable(p.x, p.y))
            return false;
    }
    // add setting of tile into cells
    for (Position p : tile->getCells()){
        mCells[p.x][p.y].setTile(tile);
    }
    return true;
}

