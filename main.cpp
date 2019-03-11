#include <iostream>
#include "Logic/CalculationCoverageAlgorithm.h"
#include "Input/InputLoader.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argv[1] == nullptr){
        return 1;
    }

    auto factory = new Factory();
    auto loader = new InputLoader(argv[1], *factory);
    if (loader->occuredFail()){
        delete factory;
        delete loader;
        return 1;
    }

    auto algorithm = new CalculationCoverageAlgorithm(*factory);
    algorithm->fillDisabledTiles(loader->getDisabledTiles());

    algorithm->process();

    cout << algorithm->getMaxValue() << endl;

    delete factory;
    delete loader;
    delete algorithm;

    return 0;
}