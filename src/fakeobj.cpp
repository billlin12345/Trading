#include <iostream>
#include <iterator>
#include <boost/algorithm/string.hpp>

#include "../include/fakeobj.hpp"
#include "../include/helperfunctions.hpp"
#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"
#include "../include/transactioncostmodeling.hpp"


namespace fake{
    // defines all the static variables
    std::map<std::string, Stock> Stock::stocks = {};    // key: ticker, value: Stock
    std::map<double,Order> Orders = {};    // key: ID, value: Order
    double Order::OrderID = 101;

    Order::~Order(){}
    Order::Order(std::string t, double price, double vol, int indi, bool visi):limitPrice(price), shares(vol), buySellIndicator(indi),visible(visi){
        ticker = helper::getUppercase(t);
      //  Order::Orders[Order::OrderID] = *this;
        if (Stock::stocks.count(ticker) == 0){   // meaning you never had the stock
            Stock::stocks[ticker] = Stock(ticker);
            Limit x = Limit(ticker, limitPrice100);     // then create limit object
            x.incrementVolume(x.getVolume() + shares);

            if (buySellIndicator == 1){
                Stock::stocks[ticker].limitsBid.at(limitPrice100) = x;
                Stock::stocks[ticker].limitsBid[limitPrice100].orders.push_back(*this);
                Stock::stocks[ticker].bestBid = limitPrice;    // initializes best bid
            }
            else if (buySellIndicator == 0){
                Stock::stocks[ticker].limitsAsk[limitPrice100] = x;
                Stock::stocks[ticker].limitsAsk[limitPrice100].orders.push_back(*this);
                Stock::stocks[ticker].bestAsk = limitPrice;    // initializes best ask
            }
            else if (buySellIndicator == -1){

            }
            else{
                std::cout << "Please designate whether you are buying, selling, or short-selling."<< std::endl;
                // break
            }
        }
        else if (buySellIndicator == 1){    // the stock exists, so define x as the thing inside
            Stock::stocks[ticker].limitsBid[limitPrice100].incrementSize(1);
            Stock::stocks[ticker].limitsBid[limitPrice100].incrementVolume(shares);
            if (limitPrice >= Stock::stocks[ticker].bestBid){
                Stock::stocks[ticker].bestBid = limitPrice;}    // replaces bestBid if buy price is higher
            Stock::stocks[ticker].limitsBid[limitPrice100].orders.push_back(*this);
        }
        else if (buySellIndicator == 0){
            Stock::stocks[ticker].limitsAsk[limitPrice100].incrementSize(1);
            Stock::stocks[ticker].limitsAsk[limitPrice100].incrementVolume(shares);
            if (limitPrice <= Stock::stocks[ticker].bestAsk || Stock::stocks[ticker].bestAsk < 0.0001){
                Stock::stocks[ticker].bestAsk = limitPrice;}    // replaces bestAsk if sell price is lower or ask is currently zero
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





    // market orders
    Order::Order(std::string t, double vol, int indi):shares(vol), buySellIndicator(indi){
        ticker = helper::getUppercase(t);
        if (buySellIndicator == 1){
            loop:
            if (shares < Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].getVolume()){ // if wanted volume < # of stocks available at the bestAsk, look at 1 order at a time.
                Order &o = Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.front();   // take out the first order
                if (shares < o.getShares()){
                    o.incrementShares(-shares); // remove the shares from the first order
                }
                else if (shares == o.getShares()){

                    Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.pop_front();    // pop if the order fits exactly
                    Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementSize(-1);     // remove one order from Limit's deque
                }
                else if (shares > o.getShares()){
                    Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.pop_front();    // pop the first order
                    Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementSize(-1);     // remove that order from Limit's deque
                    Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementVolume(-o.getShares()); // deduct volume from Limit's deque
                    shares -= o.getShares();
                    auto orderIter = Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.begin() + 1;
                    while (orderIter != Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.end()){ // keep looping until volume < orders
                        if (shares > orderIter->shares){    // if it is greater, keep taking an order off one-by-one
                            Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.pop_front();
                            Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementSize(-1);
                            Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementVolume(-orderIter->shares);
                            shares -= orderIter->shares;
                            ++ orderIter;
                        }
                        else{   // when volume finally <= shares available, goto the previous parts and finish.
                            goto loop;
                        }
                    }
                }
                Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementVolume(-shares); // deduct volume from Limit's deque
            }
            else if (shares == Stock::stocks[t].limitsAsk[Stock::stocks[ticker].bestAsk * 100].getVolume()){ // take the entire deque by deleting it all if equal.
                Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementSize(-Stock::stocks[ticker].limitsAsk[Stock::stocks[t].bestAsk * 100].getSize());
                Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].incrementVolume(-Stock::stocks[ticker].limitsAsk[Stock::stocks[t].bestAsk * 100].getVolume());
                // and move the bestAsk price
                Stock::stocks[ticker].limitsAsk[Stock::stocks[ticker].bestAsk * 100].orders.clear();
            }
            else{   // /if volume > # of stocks at bestAsk, take all at bestAsk and move bestAsk up and buy more through recursion.
                ;
            }
        }


        else if (buySellIndicator == 0){    // sell
            ;

        }
        else if (buySellIndicator == -1){
            ;
        }
        else{
            ;
            // break;
        }
    }

    // getters/incrementers
    std::string Order::getTicker() {return ticker;}
    double Order::getShares(){return shares;}
    double Order::getLimitPrice(){return limitPrice;}
    double Order::getLimitPrice100(){return limitPrice100;}
    double Order::getEntryTime(){return entryTime;}
    double Order::getEventTime(){return eventTime;}
    int Order::getBuySellIndicator(){return buySellIndicator;}
    bool Order::isVisible(){return visible;}
    double Order::getOrderID(){return orderID;}
    void Order::incrementShares(double i){shares += i;}

    Stock::~Stock(){}
    Stock::Stock(std::string t){
        ticker = helper::getUppercase(t);
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
        ticker = helper::getUppercase(t);
        size = 1;
    }

    // getters/incrementers
    double Limit::getSize(){return size;}
    double Limit::getVolume(){return volume;}
    void Limit::incrementSize(double i){
        size += i;}
    void Limit::incrementVolume(double i){volume += i;}

}
