//
// Created by Jan Matějka on 2019-03-07.
//

#include "Factory.h"

Factory::Factory() {

}

FirstTile *Factory::createFirstTile(const int x, const int y, Direction direction) {
    return new FirstTile(mFirstTypeLength, x, y, direction, mFirstTypeValue);
}

SecondTile *Factory::createSecondTile(const int x, const int y, Direction direction) {
    return new SecondTile(mSecondTypeLength, x, y, direction, mSecondTypeValue);
}

SimpleTile *Factory::createSimpleTile(const int x, const int y) {
    return new SimpleTile(1, x, y, mSimpleTypeValue);
}

DisabledTile * Factory::createDisabledTile(const int x, const int y) {
    return new DisabledTile(1, x, y, 0);
}

Table * Factory::createTable() const {
    return new Table(mHeight, mWidth);
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

}

int Factory::getDisabledCount() {
    return disabledCount;
}

void Factory::setDisabledCount(int count) {
    disabledCount = count;
}
