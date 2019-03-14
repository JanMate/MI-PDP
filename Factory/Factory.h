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
    int firstTypeLength;
    int secondTypeLength;
    int firstTypeValue;
    int secondTypeValue;
    int simpleTypeValue;
    int height;
    int width;
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

    void setFirstTypeLength(int firstTypeLength);

    int getSecondTypeLength() const;

    void setSecondTypeLength(int secondTypeLength);

    int getFirstTypeValue() const;

    void setFirstTypeValue(int firstTypeValue);

    int getSecondTypeValue() const;

    void setSecondTypeValue(int secondTypeValue);

    int getSimpleTypeValue() const;

    void setSimpleTypeValue(int simpleTypeValue);

    int getHeight() const;

    void setHeight(int height);

    int getWidth() const;

    void setWidth(int width);

    int getDisabledCount();

    void setDisabledCount(int count);
};


#endif //MI_PDP_TILEFACTORY_H
