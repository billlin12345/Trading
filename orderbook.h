#ifndef orderBOOK
#define orderBOOK

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

#include "orderbook.h"
#include "orderbooksimulation.h"
#include "webdata.h"


namespace orderbook{

class Order{    // since this is the Orderbook, all Orders HERE are assumed to be limit Orders
private:
    std::string ticker;
    double limitPrice;
    double limitPrice100 = limitPrice * 100;
    double shares;
    double entryTime;
    double eventTime;
    int buySellIndicator;    // 1 buy, -1 short sell, 0 sell
    bool visible;    // 1 yes, 0 hidden
    std::map<double,Order> Orders;  // map with <OrderID, Order> for quick access based on ID

public:
    Order();
    ~Order();
    Order(std::string t, double price, double vol, int indi, bool visi);
    static double OrderID;    // increments by 1 each Order, start at 101

    // getters
    std::string getTicker();
    double getShares();
    double getLimitPrice();
    double getLimitPrice100();
    double getEntryTime();
    double getEventTime();
    int getBuySellIndicator();
    bool isVisible();

    // execute function
};


class Stock{
private:
    std::string name;
    std::string ticker;
    std::string exchange;
    std::string exchangeSymbol;
    std::string continent;
    double currentPrice;
    double averageDailyVolume;

public:
    Stock();
    ~Stock();
    Stock(std::string t);
    //static std::map<double, std::queue<Order> > Orderbook;
    std::vector<double> limitsAsk;
    std::vector<double> limitsBid;


    // getters
    std::string getName();
    std::string getTicker();
    std::string getExchange();
    std::string getExchangeSymbol();
    std::string getContinent();
    double getCurrentPrice();
    double getAverageDailyVolume();
};


class Limit{
private:

public:
    //std::map<   // key: limit, val: Limit objcet for "random-like" access like a tree.

};






}


#endif // OrderBOOK

