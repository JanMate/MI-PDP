//
// Created by Jan Matějka on 2019-03-07.
//

#include "Factory.h"

Factory::Factory() {

}

FirstTile *Factory::createFirstTile(Position position, Direction direction) {
    return new FirstTile(mFirstTypeLength, position, direction, mFirstTypeValue);
}

SecondTile *Factory::createSecondTile(Position position, Direction direction) {
    return new SecondTile(mSecondTypeLength, position, direction, mSecondTypeValue);
}

SimpleTile *Factory::createSimpleTile(Position position) {
    return new SimpleTile(1, position, mSimpleTypeValue);
}

DisabledTile * Factory::createDisabledTile(Position position) {
    return new DisabledTile(1, position, 0);
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
