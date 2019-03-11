//
// Created by Jan Matějka on 2019-03-07.
//

#include "Factory.h"

Factory::Factory() {

}

FirstTile *Factory::createFirstTile(Position *position, Direction direction) {
    return new FirstTile(this->mFirstTypeLength, position, direction, mFirstTypeValue);
}

SecondTile *Factory::createSecondTile(Position *position, Direction direction) {
    return new SecondTile(mFirstTypeLength, position, direction, mSecondTypeValue);
}

SimpleTile *Factory::createSimpleTile(Position *position, Direction direction) {
    return new SimpleTile(1, position, mSimpleTypeValue);
}

DisabledTile *Factory::createDisabledTile(Position *position) {
    return new DisabledTile(1, position, 0);
}

Table * Factory::createTable(Position ***positions) const {
    return new Table(mHeight, mWidth, positions);
}

int Factory::getFirstTypeLength() const {
    return mFirstTypeLength;
}

void Factory::setFirstTypeLength(int mFirstTypeLength) {
    Factory::mFirstTypeLength = mFirstTypeLength;
}

int Factory::getSecondTypeLength() const {
    return mSecondTypeLength;
}

void Factory::setSecondTypeLength(int mSecondTypeLength) {
    Factory::mSecondTypeLength = mSecondTypeLength;
}

int Factory::getFirstTypeValue() const {
    return mFirstTypeValue;
}

void Factory::setFirstTypeValue(int mFirstTypeValue) {
    Factory::mFirstTypeValue = mFirstTypeValue;
}

int Factory::getSecondTypeValue() const {
    return mSecondTypeValue;
}

void Factory::setSecondTypeValue(int mSecondTypeValue) {
    Factory::mSecondTypeValue = mSecondTypeValue;
}

int Factory::getSimpleTypeValue() const {
    return mSimpleTypeValue;
}

void Factory::setSimpleTypeValue(int mSimpleTypeValue) {
    Factory::mSimpleTypeValue = mSimpleTypeValue;
}

int Factory::getHeight() const {
    return mHeight;
}

void Factory::setHeight(int mHeight) {
    Factory::mHeight = mHeight;
}

int Factory::getWidth() const {
    return mWidth;
}

void Factory::setWidth(int mWidth) {
    Factory::mWidth = mWidth;
}

Factory::~Factory() {
    for (int i = 0; i < mHeight; i++)
        delete mPositions[i];
    delete mPositions;
}

Position ***Factory::createPositions() const {
    Position*** positions = new Position**[mHeight];
    for (int i = 0; i < mHeight; i++)
        positions[i] = new Position*[mWidth];

    for (int i = 0; i < mHeight; ++i)
        for (int j = 0; j < mWidth; ++j)
            positions[i][j] = new Position(i, j);

    return positions;
}
