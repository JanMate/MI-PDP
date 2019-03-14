//
// Created by Jan Matějka on 2019-03-08.
//

#include <iostream>
#include "Table.h"

Table::Table(const int height, const int width)
            : mHeight(height), mWidth(width), mCells(static_cast<unsigned long>(height * width)),
              emptyCells(height * width), simpleTiles() {
    for (int i = 0; i < mHeight; ++i){
        for (int j = 0; j < mWidth; ++j){
            mCells[i * width + j] = 0;
        }
    }
}

Table::Table(const Table &table): mHeight(table.mHeight), mWidth(table.mWidth), mCells(table.mCells),
                                  emptyCells(table.emptyCells), simpleTiles(table.simpleTiles) {

}

Table::~Table() {

}

int & Table::getCell(const int i, const int j) {
    return mCells[i * mWidth + j];
}

void Table::setCell(const int i, const int j, const int id) {
    mCells[i * mWidth + j] = id;
}

void Table::print() {
    cout << endl;
    for (int i = 0; i < mHeight; ++i){
        for (int j = 0; j < mWidth; ++j){
            if (getCell(i, j) < 0 || getCell(i, j) > 9) {
                cout << " ";
                if (getCell(i, j) == ObjectType::Disabled)
                    cout << " Z";
                else if (getCell(i, j) == ObjectType::Simple)
                    cout << " -";
                else
                    cout << getCell(i, j);
            } else {
                cout << "  " << getCell(i, j);
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "Empty cells: " << simpleTiles.size() << " : ";
    for (Position p : simpleTiles){
        cout << p.x << "," << p.y << " ; ";
    }
    cout << endl << endl;
}

bool Table::isAvailable(const int i, const int j) {
    return mCells[i * mWidth + j] == ObjectType::Empty;
}

bool Table::situateTile(Tile *tile, const int id) {
    for (int i = 0; i < tile->getLength(); ++i){
        if ((tile->getX() + (tile->getDirection() == Direction::Horizontal ? 0 : i)) >= mHeight ||
            (tile->getY() + (tile->getDirection() == Direction::Horizontal ? i : 0)) >= mWidth ||
             !isAvailable(tile->getX() + (tile->getDirection() == Direction::Horizontal ? 0 : i),
                          tile->getY() + (tile->getDirection() == Direction::Horizontal ? i : 0)))
            return false;
    }
    // add setting of tile into cells
    for (int i = 0; i < tile->getLength(); ++i){
        setCell(tile->getX() + (tile->getDirection() == Direction::Horizontal ? 0 : i),
                tile->getY() + (tile->getDirection() == Direction::Horizontal ? i : 0), (tile->getType() == ObjectType::Simple ? ObjectType::Simple : id));
        emptyCells--;
    }
    if (tile->getType() == ObjectType::Simple)
        simpleTiles.emplace_back(tile->getX(), tile->getY());
    return true;
}

int Table::getCountOfEmptyCells() {
    return emptyCells;
}

void Table::decrementFreeCell() {
    emptyCells--;
}

