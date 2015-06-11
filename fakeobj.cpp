#include <iostream>
#include <boost/algorithm/string.hpp>

#include "fakeobj.h"
#include "algorithms.h"
#include "fakeobj.h"
#include "orderbook.h"
#include "orderbooksimulation.h"
#include "transactioncostmodeling.h"
#include "webdata.h"

namespace fake{

    Order::Order(){}
    Order::~Order(){}
    Order::Order(std::string t, double price, double vol, int indi, bool visi):limitPrice(price), shares(vol), buySellIndicator(indi),visible(visi){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        //OrderID += 1;   // forgot if need getter/setter for changing this
        //if (ticker.Order) // .............. actually maybe don't need to check since Order is always added when initialized?
    }

    // getters
    std::string Order::getTicker() {return ticker;}
    double Order::getShares(){return shares;}
    double Order::getLimitPrice(){return limitPrice;}
    double Order::getLimitPrice100(){return limitPrice100;}
    double Order::getEntryTime(){return entryTime;}
    double Order::getEventTime(){return eventTime;}
    int Order::getBuySellIndicator(){return buySellIndicator;}
    bool Order::isVisible(){return visible;}


    Stock::Stock(){}
    Stock::~Stock(){}
    Stock::Stock(std::string t){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        name = ticker + " Name";
    }   // add the web stuff to constructor init list

    std::string Stock::getName() {return name;}
    std::string Stock::getTicker() {return ticker;}
    std::string Stock::getExchange() {return exchange;}
    std::string Stock::getExchangeSymbol() {return exchangeSymbol;}
    std::string Stock::getContinent(){return continent;}
    double Stock::getCurrentPrice() {return currentPrice;}
    double Stock::getAverageDailyVolume(){return averageDailyVolume;}

}
