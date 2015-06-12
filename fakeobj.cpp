#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>

#include "fakeobj.h"
#include "algorithms.h"
#include "fakeobj.h"
#include "orderbook.h"
#include "orderbooksimulation.h"
#include "transactioncostmodeling.h"
#include "webdata.h"

namespace fake{
    //  std::map<std::string, Limit> Stock::stocks = {}; // right
    std::map<std::string, Stock> Stock::stocks = {}; // test

    Order::Order(){}
    Order::~Order(){}
    Order::Order(std::string t, double price, double vol, int indi, bool visi):limitPrice(price), shares(vol), buySellIndicator(indi),visible(visi){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        Limit x = Limit(ticker, limitPrice100); // check if Limit obj exists first??

        Stock y = Stock (ticker); // delete! // nvm, this is also part of the test

        // Stock::stocks[ticker] = x;  // this is correct,
        Stock::stocks[ticker] = y;  // test

        std::cout << "1";

        if (buySellIndicator == 1){
            //y.limitsBid[this->limitPrice100].orders.push_back(*this); // Stock.stocks[GOOG].limitsBd
            //ticker.limitsBid[Order.limitPrice100] = x;
        std::cout << "2";
            this->limitPrice100 = 10;   // delete this later, only to test small numbers
            y.limitsBid[this->limitPrice100] = x;// further test THIS LINE BREAKS@@@@@@@
            std::cout << "3";
            //  Stock::stocks[ticker].orders.push_back(*this);  // this is correct
            y.limitsBid[this->limitPrice100].orders.push_back(*this);//  // test
        std::cout << "4";
        }
        else if (buySellIndicator == 0){
            ;//Stock.limitsAsk[Order.limitPrice100] = 0;//
        }
        else if (buySellIndicator == -1){
            ;
        }
        else{
            std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
            // break
        }

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
    // get orderID

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
        // stocks[ticker] = *this;   // doesn't work for static containers ...
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
