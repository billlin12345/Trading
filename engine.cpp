#include <string>

#include "engine.h"
#include "orderbook.h"
#include "transactioncostmodeling.h"

// include init

namespace engine {

    tradingProg::tradingProg(){assetClassType = 0;}
    tradingProg::tradingProg(int assetClass):assetClassType(assetClass){
    // case to output what type of engine it is, and how to initialize.
    // initialize
    tradingProg::matchMake();
    }

    // functions
    bool tradingProg::isEngineRunning(){
        return tradingProg::isRunning;
    }

    void tradingProg::matchMake(){
        //while (){   // no errors, trading hours/day

        //}
    }

}
