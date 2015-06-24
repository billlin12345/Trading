#include <iostream>
#include <string>
#include <map>
#include <queue>

#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"
#include "../include/webdata.hpp"

namespace orderbook{
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
    if (Stock::stocks.count(ticker) == 0){   // meaning you never had the stock
        Stock y = Stock (ticker);
        Stock::stocks[ticker] = y;  // inserts the stock into the map
        Limit x = Limit(ticker, limitPrice100);     // then create limit object
        x.setVolume(x.getVolume() + shares);

        if (buySellIndicator == 1){
            Stock::stocks[ticker].limitsBid[limitPrice100] = x;
            y.limitsBid[this->limitPrice100] = x;
            y.limitsBid[this->limitPrice100].orders.push_back(*this);

        }
        else if (buySellIndicator == 0){
            Stock::stocks[ticker].limitsAsk[limitPrice100] = x;
            y.limitsAsk[this->limitPrice100] = x;
            y.limitsAsk[this->limitPrice100].orders.push_back(*this);

        }
        else if (buySellIndicator == -1){

        }
        else{
            std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
            // break
        }
    }
    else if (buySellIndicator == 1){  // the stock exists, so define x as the thing inside
        Limit &x = Stock::stocks[ticker].limitsBid[limitPrice100];
        x.setSize(x.getSize() + 1);
        x.setVolume(x.getVolume() + shares);
        Stock &y = Stock::stocks[ticker];

        y.limitsBid[this->limitPrice100] = x;
        y.limitsBid[this->limitPrice100].orders.push_back(*this);
    }
    else if (buySellIndicator == 0){
        Limit &x = Stock::stocks[ticker].limitsAsk[limitPrice100];
        x.setSize(x.getSize() + 1);
        x.setVolume(x.getVolume() + shares);
        Stock &y = Stock::stocks[ticker];
        y.limitsAsk[this->limitPrice100] = x;
        y.limitsAsk[this->limitPrice100].orders.push_back(*this);

    }
    else if (buySellIndicator == -1){
        ;
    }
    else{
        std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
        // break
    }

    orderID = Order::OrderID;
    ++Order::OrderID;
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



    Limit::Limit(){
    size = 1;
    }
    Limit::~Limit(){}
    Limit::Limit(std::string t, double price):limitPrice(price){
    for(auto i=0; t[i]; ++i){
        t[i] = toupper(t[i]);
    }
    ticker = t;
    size = 1;
    }

    // getters
    double Limit::getSize(){return size;}
    double Limit::getVolume(){return volume;}

    // setters
    void Limit::setSize(double i){size = i;}
    void Limit::setVolume(double i){volume = i;}



}

