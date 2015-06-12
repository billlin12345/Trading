#ifndef FAKEOBJ
#define FAKEOBJ

#include <map>
#include <deque>
#include <vector>

#include "orderbook.hpp"
#include "orderbooksimulation.hpp"

namespace fake{

class Order{    // since this is the Orderbook, all Orders HERE are assumed to be limit Orders

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
    double getOrderID();

    // execute function
};


class Limit{
private:
    std::string ticker;
    double limitPrice;
    double size;
    double volume;

public:
    Limit();
    ~Limit();
    Limit(std::string t, double price);
    //std::map<   // key: limit, val: Limit objcet for "random-like" access like a tree.
    std::deque<Order> orders;
    double getSize();
    double getVolume();
};


class Stock{
private:
    std::string name= "Apple";
    std::string ticker = "AAPL";
    std::string exchange;
    std::string exchangeSymbol;
    std::string continent;
    double currentPrice = rand()%100 + 15;
    double averageDailyVolume;

public:
    Stock();
    ~Stock();
    Stock(std::string t);
    static std::map<double, std::queue<orderbook::Order> > Orderbook;
    std::vector<Limit> limitsAsk;
    std::vector<Limit> limitsBid;

    static std::map<std::string, Stock> stocks;     // wrong

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
