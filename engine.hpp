#ifndef ENGINE_H
#define ENGINE_H

namespace engine {

class tradingProg{
public:
    // constructors
    tradingProg();
    ~tradingProg();
    tradingProg(int assetClass);

    // functions
    bool isEngineRunning();
    void matchMake();


private:
    int assetClassType; // 1 is stocks, 2 is options, 3 is combination of 1 and 2, 0 is simulation, use enum?
    bool isRunning;


};
}

#endif // ENGINE_H

