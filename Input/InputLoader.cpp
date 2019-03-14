//
// Created by Jan Matějka on 2019-03-08.
//

#include <iostream>
#include <fstream>
#include "InputLoader.h"

InputLoader::InputLoader(char *fileName, Factory &factory) {
     ifstream file;
    file.open(fileName);

    if (!file){
        printFaultAndCloseFile("Can not read file " + string(fileName) + "!", file);
        return;
    }
    int tmp = 0;

    // first line in file
    file >> tmp;
    factory.setHeight(tmp);
    file >> tmp;
    factory.setWidth(tmp);


    // second line in file
    file >> tmp;
    if (tmp <= 2) {
        printFaultAndCloseFile("Too short length of first type tile!", file);
        return;
    }
    factory.setFirstTypeLength(tmp);

    file >> tmp;
    if (tmp <= factory.getFirstTypeLength()) {
        printFaultAndCloseFile("Too short length of second type tile!", file);
        return;
    }
    factory.setSecondTypeLength(tmp);

    file >> tmp;
    if (tmp <= 0) {
        printFaultAndCloseFile("Too low value of first type tile!", file);
        return;
    }
    factory.setFirstTypeValue(tmp);

    file >> tmp;
    if (tmp <= factory.getFirstTypeValue()) {
        printFaultAndCloseFile("Too low value of second type tile!", file);
        return;
    }
    factory.setSecondTypeValue(tmp);

    file >> tmp;
    if (tmp >= 0) {
        printFaultAndCloseFile("Positive value of penalization!", file);
        return;
    }
    factory.setSimpleTypeValue(tmp);

    // the rest of file
    file >> tmp;
    if (tmp >= factory.getHeight() * factory.getWidth()) {
        printFaultAndCloseFile("Bad number of disabled tiles!", file);
        return;
    }
    factory.setDisabledCount(tmp);

    int x, y;
    for (int i = 0; i < tmp; ++i){
        file >> y >> x;
        if (x < 0 || x >= factory.getHeight() || y < 0 || y >= factory.getWidth()) {
            printFaultAndCloseFile("Bad number of disabled tiles!", file);
            return;
        }
        disabledTiles.push_back(factory.createDisabledTile(x, y));
    }

    file.close();
}

InputLoader::~InputLoader() {
    for (DisabledTile* tile : disabledTiles){
        delete tile;
    }
}

list<DisabledTile *> InputLoader::getDisabledTiles() const {
    return disabledTiles;
}

void InputLoader::printFaultAndCloseFile(string message, ifstream &file) {
    cerr << message << endl;
    fail = true;
    file.close();
}

bool InputLoader::failOccurred() {
    return fail;
}
