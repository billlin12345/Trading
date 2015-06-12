#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>

#include "fakeobj.hpp"
#include "algorithms.hpp"
#include "fakeobj.hpp"
#include "orderbook.hpp"
#include "orderbooksimulation.hpp"
#include "transactioncostmodeling.hpp"
#include "webdata.hpp"

namespace fake{
    // defines all the static variables
    std::map<std::string, Stock> Stock::stocks = {};
    double Order::OrderID = 101;

    Order::Order(){}
    Order::~Order(){}
    Order::Order(std::string t, double price, double vol, int indi, bool visi):limitPrice(price), shares(vol), buySellIndicator(indi),visible(visi){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        Limit x = Limit(ticker, limitPrice100); // check if Limit obj exists first?
        Stock y = Stock (ticker);
        Stock::stocks[ticker] = y;
        orderID = Order::OrderID;
        ++Order::OrderID;

        if (buySellIndicator == 1){
            y.limitsBid[this->limitPrice100] = x;
            y.limitsBid[this->limitPrice100].orders.push_back(*this);
        }
        else if (buySellIndicator == 0){
            ;
        }
        else if (buySellIndicator == -1){
            ;
        }
        else{
            std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
            // break
        }

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
    double Order::getOrderID(){return orderID;}

    Stock::Stock(){}
    Stock::~Stock(){}
    Stock::Stock(std::string t){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        name = ticker + " Name";
        this->limitsAsk.resize(35000);
        this->limitsBid.resize(35000);
    }   // add the web stuff to constructor init list

    std::string Stock::getName() {return name;}
    std::string Stock::getTicker() {return ticker;}
    std::string Stock::getExchange() {return exchange;}
    std::string Stock::getExchangeSymbol() {return exchangeSymbol;}
    std::string Stock::getContinent(){return continent;}
    double Stock::getCurrentPrice() {return currentPrice;}
    double Stock::getAverageDailyVolume(){return averageDailyVolume;}

    Limit::Limit(){}
    Limit::~Limit(){}
    Limit::Limit(std::string t, double price):ticker(t),limitPrice(price){}
    double Limit::getSize(){return size;}
    double Limit::getVolume(){return volume;}


}
