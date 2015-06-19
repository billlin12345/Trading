#include <iostream>
#include <iomanip>

#include "../include/graphing.hpp"

namespace orderbook{

void displayGraph(std::string ticker){
    std::cout << "                                          Orderbook for " << ticker << "\n";
    double lowerRange, upperRange, temp;
    lowerRange = fake::Stock::stocks[ticker].bestBid - .25;  // +- 25 cents
    upperRange = fake::Stock::stocks[ticker].bestAsk + .25;  // for-loop to update this?
    for(auto i = lowerRange; i <= fake::Stock::stocks[ticker].bestBid; i += 0.01){
        temp = fake::Stock::stocks[ticker].limitsBid[i * 100].getVolume() / 10;
        if (temp < 0.000001)
            temp = 0;
        std::cout << std::setprecision(2) << std::fixed << i << ": " ;    // i is the limitPrice100
            for  (auto k = 0; k < temp; ++k)
                std::cout << '*';
            if (temp >= 0.000001)
                std::cout << "     " << std::setprecision(0) << temp;
        std::cout << "\n";

    }

    // for loop to create the empty void between bestBid and bestAsk
    for (auto m = fake::Stock::stocks[ticker].bestBid + 0.01; m < fake::Stock::stocks[ticker].bestAsk; m += 0.01){
        std::cout << m << ": \n";
    }

    for (auto j = fake::Stock::stocks[ticker].bestAsk; j <= upperRange; j += 0.01){
        temp = fake::Stock::stocks[ticker].limitsAsk[j * 100].getVolume() / 10; // check if boundaries are accurate
        if (temp < 0.000001)
            temp = 0;
        std::cout << std::setprecision(2) << j << ": " ;    // j is the limitPrice100
            for  (auto k = 0; k < temp; ++k)
                std::cout << '*';
            if (temp >= 0.000001)
                std::cout << "     " << std::setprecision(0) << temp;
        std::cout << std::setprecision(2) << "\n";

    }

}

/*
updateGraph(){  // adds each order in

}
*/

/*
displayGraphContinuously(){  // adds each order in

}
*/

}
