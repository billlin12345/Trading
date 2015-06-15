#include <iostream>
#include <cmath>

#include "../include/transactioncostmodeling.hpp"
#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"

class TCA{
public:

    TCA();
    ~TCA();

    double calcSlippage(std::string ticker){

        return slippage;
    }

    void calcLiquidity(std::string ticker, double liquidityArr[]){
    }

    double calcTotalTransactionCosts(std::string ticker, double transactionCosts[]){  // calculates components inside transactionCosts and returns total or based on various measures
        return totalTransactionCosts;
    }

    double calceMarketImpact(int MIModel){
        switch(MIModel){

        case 1:{    // Bloomberg
            double alpha = 0.025;   // +- 0.0014
            double beta1 = 0.76;    // +- 0.06
            double beta2 = 0.19;    // +- 0.0017
            double gamma = 0.030;   // +- 0.0017
            double n = 0.81;        // +- 0.08
            double spreadPercentage;
            double tradeDuration;
            double volatility;
            double partRate;
            double ADV;
            double size;    // volume
            double lambda = -0.25 + 3 * (std::max(std::min(0.3,partRate/100),0.05) - 0.05);
            return lambda * spreadPercentage + alpha * volatility * std::pow(partRate/100,beta1) * std::pow(tradeDuration,beta2) + gamma * volatility * std::pow(size/ADV,n);
        }
        case 2:{
            break;
        }
        case 3:{
            break;
        }
        }
    }


private:
    double liquidityArr[];
    double transactionCosts[];
    double slippage;
    double commission;
    double tax;
    double totalTransactionCosts;

};
