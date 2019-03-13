#include <iostream>
#include "Logic/CalculationCoverageAlgorithm.h"
#include "Input/InputLoader.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argv[1] == nullptr){
        return 1;
    }

    auto factory = new Factory();
    auto loader = InputLoader(argv[1], *factory);
    if (loader.occuredFail()){
        delete factory;
        return 1;
    }

    auto algorithm = CalculationCoverageAlgorithm(*factory);
    algorithm.fillDisabledTiles(loader.getDisabledTiles());

    algorithm.process();

    algorithm.getBestTable().print();
    cout << "Best value: " << algorithm.getBestValue() << endl;

    delete factory;

    return 0;
}