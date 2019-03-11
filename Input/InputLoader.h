//
// Created by Jan Matějka on 2019-03-08.
//

#ifndef MI_PDP_INPUTLOADER_H
#define MI_PDP_INPUTLOADER_H

#include <string>
#include <list>
#include "../Factory/Factory.h"

using namespace std;

class InputLoader {
private:
    list<DisabledTile*> disabledTiles;
    bool fail = false;

    void printFaultAndCloseFile(string message, ifstream &file);
public:
    InputLoader(char *fileName, Factory &factory);

    ~InputLoader();

    list<DisabledTile*> getDisabledTiles() const;

    bool occuredFail();
};


#endif //MI_PDP_INPUTLOADER_H
