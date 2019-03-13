//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_TILEFACTORY_H
#define MI_PDP_TILEFACTORY_H


#include "../Object/Tile.h"
#include "../Object/FirstTile.h"
#include "../Object/SecondTile.h"
#include "../Object/SimpleTile.h"
#include "../Object/DisabledTile.h"
#include "../Object/Table.h"

class Factory {
private:
    int mFirstTypeLength;
    int mSecondTypeLength;
    int mFirstTypeValue;
    int mSecondTypeValue;
    int mSimpleTypeValue;
    int mHeight;
    int mWidth;
    int disabledCount = 0;

public:
    Factory();

    ~Factory();

    FirstTile* createFirstTile(const int x, const int y, Direction direction);

    SecondTile* createSecondTile(const int x, const int y, Direction direction);

    SimpleTile *createSimpleTile(const int x, const int y);

    DisabledTile * createDisabledTile(const int x, const int y);

    Table *createTable() const;

    int getFirstTypeLength() const;

    void setFirstTypeLength(int mFirstTypeLength);

    int getSecondTypeLength() const;

    void setSecondTypeLength(int mSecondTypeLength);

    int getFirstTypeValue() const;

    void setFirstTypeValue(int mFirstTypeValue);

    int getSecondTypeValue() const;

    void setSecondTypeValue(int mSecondTypeValue);

    int getSimpleTypeValue() const;

    void setSimpleTypeValue(int mSimpleTypeValue);

    int getHeight() const;

    void setHeight(int mHeight);

    int getWidth() const;

    void setWidth(int mWidth);

    int getDisabledCount();

    void setDisabledCount(int count);
};


#endif //MI_PDP_TILEFACTORY_H
