//
// Created by Jan Matějka on 2019-03-07.
//

#include "Factory.h"

Factory::Factory() { }

FirstTile *Factory::createFirstTile(const int x, const int y, Direction direction) {
    return new FirstTile(firstTypeLength, x, y, direction, firstTypeValue);
}

SecondTile *Factory::createSecondTile(const int x, const int y, Direction direction) {
    return new SecondTile(secondTypeLength, x, y, direction, secondTypeValue);
}

SimpleTile *Factory::createSimpleTile(const int x, const int y) {
    return new SimpleTile(1, x, y, simpleTypeValue);
}

DisabledTile * Factory::createDisabledTile(const int x, const int y) {
    return new DisabledTile(1, x, y, 0);
}

Table * Factory::createTable() const {
    return new Table(height, width);
}

int Factory::getFirstTypeLength() const {
    return firstTypeLength;
}

void Factory::setFirstTypeLength(int firstTypeLength) {
    Factory::firstTypeLength = firstTypeLength;
}

int Factory::getSecondTypeLength() const {
    return secondTypeLength;
}

void Factory::setSecondTypeLength(int secondTypeLength) {
    Factory::secondTypeLength = secondTypeLength;
}

int Factory::getFirstTypeValue() const {
    return firstTypeValue;
}

void Factory::setFirstTypeValue(int firstTypeValue) {
    Factory::firstTypeValue = firstTypeValue;
}

int Factory::getSecondTypeValue() const {
    return secondTypeValue;
}

void Factory::setSecondTypeValue(int secondTypeValue) {
    Factory::secondTypeValue = secondTypeValue;
}

int Factory::getSimpleTypeValue() const {
    return simpleTypeValue;
}

void Factory::setSimpleTypeValue(int simpleTypeValue) {
    Factory::simpleTypeValue = simpleTypeValue;
}

int Factory::getHeight() const {
    return height;
}

void Factory::setHeight(int height) {
    Factory::height = height;
}

int Factory::getWidth() const {
    return width;
}

void Factory::setWidth(int width) {
    Factory::width = width;
}

Factory::~Factory() {

}

int Factory::getDisabledCount() {
    return disabledCount;
}

void Factory::setDisabledCount(int count) {
    disabledCount = count;
}
