#include <iostream>
#include <string>
#include <map>
#include <queue>

#include "orderbook.h"
#include "webdata.h"


namespace orderbook{
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
    double Order::getShares(){return shares;}
    double Order::getLimitPrice(){return limitPrice;}
    double Order::getLimitPrice100(){return limitPrice100;}
    double Order::getEntryTime(){return entryTime;}
    double Order::getEventTime(){return eventTime;}
    int Order::getBuySellIndicator(){return buySellIndicator;}
    bool Order::isVisible(){return visible;}



    Stock::Stock(){}
    Stock::~Stock(){}
    Stock::Stock(std::string t):ticker(t){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
    }   // add the web stuff to constructor init list

    std::string Stock::getName() {return name;}
    std::string Stock::getTicker() {return ticker;}
    std::string Stock::getExchange() {return exchange;}
    std::string Stock::getExchangeSymbol() {return exchangeSymbol;}
    std::string Stock::getContinent(){return continent;}
    double Stock::getCurrentPrice() {return currentPrice;}
    double Stock::getAverageDailyVolume(){return averageDailyVolume;}

}