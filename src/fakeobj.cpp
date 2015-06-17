#include <iostream>
#include <boost/algorithm/string.hpp>

#include "../include/fakeobj.hpp"
#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"
#include "../include/transactioncostmodeling.hpp"


namespace fake{
    // defines all the static variables
    std::map<std::string, Stock> Stock::stocks = {};    // key: ticker, value: Stock
    std::map<double,Order> Orders = {}; // key: ID, value: Order
    double Order::OrderID = 101;

    Order::~Order(){}
    Order::Order(std::string t, double price, double vol, int indi, bool visi):limitPrice(price), shares(vol), buySellIndicator(indi),visible(visi){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }

        ticker = t;
        if (Stock::stocks.count(ticker) == 0){   // meaning you never had the stock
            Stock::stocks[ticker] = Stock(ticker);
            Limit x = Limit(ticker, limitPrice100);     // then create limit object
            x.setVolume(x.getVolume() + shares);
            if (buySellIndicator == 1){
                Stock::stocks[ticker].limitsBid.at(limitPrice100) = x;
                Stock::stocks[ticker].limitsBid[limitPrice100].orders.push_back(*this);
                Stock::stocks[ticker].bestBid = limitPrice; // initializes best bid
            }
            else if (buySellIndicator == 0){
                Stock::stocks[ticker].limitsAsk[limitPrice100] = x;
                Stock::stocks[ticker].limitsAsk[limitPrice100].orders.push_back(*this);
                Stock::stocks[ticker].bestAsk = limitPrice; // initializes best ask
            }
            else if (buySellIndicator == -1){

            }
            else{
                std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
                // break
            }
        }
        else if (buySellIndicator == 1){  // the stock exists, so define x as the thing inside
            Stock::stocks[ticker].limitsBid[limitPrice100].setSize(Stock::stocks[ticker].limitsBid[limitPrice100].getSize() + 1);
            Stock::stocks[ticker].limitsBid[limitPrice100].setVolume(Stock::stocks[ticker].limitsBid[limitPrice100].getVolume() + shares);
            if (limitPrice >= Stock::stocks[ticker].bestBid){
                Stock::stocks[ticker].bestBid = limitPrice;}   // replaces bestBid if buy price is higher
            Stock::stocks[ticker].limitsBid[limitPrice100].orders.push_back(*this);
        }
        else if (buySellIndicator == 0){
            Stock::stocks[ticker].limitsAsk[limitPrice100].setSize(Stock::stocks[ticker].limitsAsk[limitPrice100].getSize() + 1);
            Stock::stocks[ticker].limitsAsk[limitPrice100].setVolume(Stock::stocks[ticker].limitsAsk[limitPrice100].getVolume() + shares);
            if (limitPrice <= Stock::stocks[ticker].bestAsk || Stock::stocks[ticker].bestAsk < 0.0001){
                Stock::stocks[ticker].bestAsk = limitPrice;}   // replaces bestAsk is sell price is lower
            Stock::stocks[ticker].limitsAsk[limitPrice100].orders.push_back(*this);

        }
        else if (buySellIndicator == -1){   // short sell
            ;
        }
        else{
            std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
            // break
        }

        orderID = Order::OrderID;
        ++Order::OrderID;
    }   // end limit Order constructor

    Order::Order(std::string t, double vol, int indi):shares(vol), buySellIndicator(indi){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        // buy sell here
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

    Stock::~Stock(){}
    Stock::Stock(std::string t){
        for(auto i=0; t[i]; ++i){
            t[i] = toupper(t[i]);
        }
        ticker = t;
        name = ticker + " Name";
        this->limitsAsk.resize(35000);
        this->limitsBid.resize(35000);
    }

    std::string Stock::getName() {return name;}
    std::string Stock::getTicker() {return ticker;}
    std::string Stock::getExchange() {return exchange;}
    std::string Stock::getExchangeSymbol() {return exchangeSymbol;}
    std::string Stock::getContinent(){return continent;}
    double Stock::getCurrentPrice() {return currentPrice;}
    double Stock::getAverageDailyVolume(){return averageDailyVolume;}

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
