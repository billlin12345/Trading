#ifndef FAKEOBJ
#define FAKEOBJ

#include <map>
#include <deque>
#include <vector>
#include <string>
#include <queue>

#include "orderbooksimulation.hpp"
#include "engine.hpp"

namespace fake{

class Order{
private:
    std::string ticker;
    double limitPrice = rand()%100 + 15;
    double limitPrice100 = limitPrice * 100;
    double shares = 200;
    double entryTime;
    double eventTime;
    double orderID;
    int buySellIndicator;    // 1 buy, -1 short sell, 0 sell
    bool visible;    // 1 yes, 0 hidden

public:
    //  Order();
    ~Order();
    Order(std::string t, double price, double vol, int indi, bool visi);
    Order(std::string t, double vol, int indi);
    static double OrderID;    // increments by 1 each Order, start at 101
    static std::map<double,Order> Orders;  // map with <OrderID, Order> for quick access based on ID

    // getters
    std::string getTicker();
    double getShares();
    double getLimitPrice();
    double getLimitPrice100();
    double getEntryTime();
    double getEventTime();
    int getBuySellIndicator();
    bool isVisible();
    double getOrderID();
};


class Limit{
private:
    std::string ticker;
    double limitPrice;
    double size;
    double volume;

public:
    Limit(){
}

    Limit(const Limit &l){
        ticker = l.ticker;
        size = l.size;
        volume = l.volume;
        orders = l.orders;
    }

    ~Limit();
    Limit(std::string t, double price);
    //std::map<   // key: limit, val: Limit object for "random-like" access like a tree.
    std::deque<Order> orders;
    double getSize();
    double getVolume();
    void setSize(double i);
    void setVolume(double i);
};


class Stock{
private:
    std::string name;
    std::string ticker;
    std::string exchange;
    std::string exchangeSymbol;
    std::string continent;
    double currentPrice;    // = rand()%100 + 15;
    double averageDailyVolume;

public:
    Stock(){
        this->limitsAsk.resize(35000);
        this->limitsBid.resize(35000);
    }
/*
    Stock(const Stock &s){
        ticker = s.ticker;
        currentPrice = s.currentPrice;
        name = ticker + " Name";
        bestAsk = s.bestAsk;
        bestBid = s.bestBid;

        this->limitsAsk.resize(35000);
        this->limitsBid.resize(35000);
        limitsAsk = s.limitsAsk;
        limitsBid = s.limitsBid;
    }
*/
    ~Stock();
    Stock(std::string t);
    static std::map<double, std::queue<fake::Order> > Orderbook;    // this is useless?
    std::vector<Limit> limitsAsk;
    std::vector<Limit> limitsBid;
    double bestAsk;
    double bestBid;

    static std::map<std::string, Stock> stocks;


    // getters
    std::string getName();
    std::string getTicker();
    std::string getExchange();
    std::string getExchangeSymbol();
    std::string getContinent();
    double getCurrentPrice();
    double getAverageDailyVolume();
};

}

#endif // FAKEOBJ
