/*  TODO
 * - finish making orderbook (initializing all the vars/selling/execution/canceling)
 * - Clean up all the include files in the headers.
 * - Add visibility condition.
 * - Unit test volume/size of Limit's and also the order queue.
 * - Make the to caps and date in to a helper functions header file
 * - Limit object should be limitPrice instead of limitPrice100?
 * - Refactor this awful code.
 *
 */

/* Possible bugs/issues:
 *
 *
 *
 */

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <time.h>

#include <curl/curl.h>
#include "../include/catch.hpp"
//#include "../include/quandl.hpp"
/// https://github.com/zafuer/QuandlAPI_C

#include "../include/algorithms.hpp"
#include "../include/fakeobj.hpp"
#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"
#include "../include/transactioncostmodeling.hpp"
#include "../include/webdata.hpp"
#include "../cointegration/JohansenHelper.h"

// Gets current date/time, format is YYYY-MM-DD.hppH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

TEST_CASE("Consecutive Fake Orders and Checking Order Class Members"){
    //fake::Order fakeOrderDefault;
    fake::Order fakeOrderGOOG102("GOOG", 102, 200, 1, 1);   // order 101
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 1);
    fake::Order ("GOOG", 102, 500, 1, 1);   // order 102
    fake::Order fakeOrderGOOG102Again("GOOG", 102, 100, 1, 1);  // order 103
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 3);
    fake::Order z = fake::Order ("GOOG", 102, 10, 1, 0);    // order 104
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 4);
    CHECK(fakeOrderGOOG102.getTicker() == "GOOG");
    CHECK(fakeOrderGOOG102.getShares() == 200);
    CHECK(fakeOrderGOOG102.getLimitPrice() == 102);
    CHECK(fakeOrderGOOG102.isVisible() == 1);
    CHECK(fakeOrderGOOG102.isVisible() == true);
    CHECK(fakeOrderGOOG102Again.getOrderID() == 103);   // change this based on how many orders
    CHECK(z.getTicker() == "GOOG");
    CHECK(z.getShares() == 10);
    CHECK(z.getLimitPrice() == 102);
    CHECK(z.isVisible() == 0);
    CHECK(z.isVisible() == false);
    CHECK(z.getOrderID() == 104);   // change this based on how many orders
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getVolume() == 810);
  //  CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 51);
    //adding or removing this line changes the outputs of bestBid/bestAsk to zero
    // if you dont do it, seg error
    std::cout << "test" << std::endl;
    std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
}

TEST_CASE("Tracking BestAsk and BestBid Prices"){
    fake::Order("AAPL", 80, 100, 1, 1);
    CHECK(fake::Stock::stocks["AAPL"].bestBid == 80);
    fake::Order("aapl", 120, 100, 1, 1);
    CHECK(fake::Stock::stocks["AAPL"].bestBid == 120);
    fake::Order("aapl", 110, 100,1,1);
    CHECK(fake::Stock::stocks["AAPL"].bestBid == 120);
    fake::Order("aapl", 140, 100,0,1);
    CHECK(fake::Stock::stocks["AAPL"].bestAsk == 140);
    fake::Order("aapl", 130, 100,0,1);
    CHECK(fake::Stock::stocks["AAPL"].bestAsk == 130);
    fake::Order("AAPL", 180, 100,0,1);
    CHECK(fake::Stock::stocks["AAPL"].bestAsk == 130);
    fake::Order("aapl", 100, 100,0,1);
    fake::Order z = fake::Order ("aapl", 110, 250, 1, 0);    // order 112
    CHECK(z.getOrderID() == 112);
    fake::Order("aapl", 100, 100,0,1);
    fake::Order("aapl", 120, 100,1,1);
    fake::Order("aapl", 110, 100,1,1);
    fake::Order("aapl", 110, 100,0,1);
}

/*TEST_CASE("Buys and Sells"){
    fake::Order("goog", 200, 100, 1, 1);
    fake::Order("goog", 100, 100, 0, 1);
    // BUY
    //SELL
}*/
