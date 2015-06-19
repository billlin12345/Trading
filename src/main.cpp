/*  TODO
 * - finish making orderbook (initializing all the vars/selling/execution/canceling)
 * - Clean up all the include files in the headers.
 * - Add visibility condition.
 * - Unit test volume/size of Limit's and also the order queue.
 * - Make the to caps and date in to a helper functions header file
 * - Limit object should be limitPrice instead of limitPrice100?
 * - Double's and 0; making sure it's not e^-317 DONE
 * - graphing: consider volume not divisible by 10
 *     - set * to 100 ? what about closer to the bid/ask
 *     - change to a graphing library
 * - clean up buffers (using \n instead of endl unless buffer needs to be flushed
 * - What is being affected by precision(2) after drawing the orderbook? rounding problems??
 * - Refactor this awful code.
 *
 */

/* Possible bugs/issues:
 * fake::Order z = fake::Order breaks bestAsk/bestBid (constructor?)
 *
 */

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>

#include <curl/curl.h>
#include "../include/catch.hpp"
//#include "../include/quandl.hpp"
/// https://github.com/zafuer/QuandlAPI_C

#include "../include/algorithms.hpp"
#include "../include/fakeobj.hpp"
#include "../include/graphing.hpp"
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
    fake::Order ("GOOG", 102, 550, 1, 1);   // order 102
    fake::Order fakeOrderGOOG102Again("GOOG", 102, 100, 1, 1);  // order 103
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 3);
    fake::Order z = fake::Order ("GOOG", 102, 10, 1, 0);    // order 104
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 4);
    CHECK(fakeOrderGOOG102.getTicker() == "GOOG");
    CHECK(fakeOrderGOOG102.getShares() == 200);
    CHECK(fakeOrderGOOG102.getLimitPrice() == 102);
    CHECK(fakeOrderGOOG102.isVisible() == 1);
    CHECK(fakeOrderGOOG102.isVisible() == true);
    CHECK(fakeOrderGOOG102Again.getOrderID() == 103);
    CHECK(z.getTicker() == "GOOG");
    CHECK(z.getShares() == 10);
    CHECK(z.getLimitPrice() == 102);
    CHECK(z.isVisible() == 0);
    CHECK(z.isVisible() == false);
    CHECK(z.getOrderID() == 104);
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getVolume() == 860);
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
    //fake::Order z = fake::Order ("aapl", 110, 250, 1, 0); // this breaks bestAsk/bestBid
    //CHECK(z.getOrderID() == 112);
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

TEST_CASE("Checking BestBid and BestAsk for Prices with DecimalPoints"){
    fake::Order("TSLA", 80.99, 100, 0, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestAsk == 80.99);
    fake::Order("TSLA", 81.02, 300, 0, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestAsk == 80.99);
    fake::Order("TSLA", 80.94, 100, 0, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestAsk == 80.94);
    fake::Order("TSLA", 81, 500, 0, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestAsk == 80.94);
    fake::Order("TSLA", 78.94, 200, 1, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestBid == 78.94);
    fake::Order("TSLA", 79.02, 100, 1, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestBid == 79.02);
    fake::Order("TSLA", 79.02, 200, 1, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestBid == 79.02);
    fake::Order("TSLA", 79.02, 200, 1, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestBid == 79.02);
    fake::Order("TSLA", 79.11, 200, 1, 1);
    CHECK(fake::Stock::stocks["TSLA"].bestBid == 79.11);
}


TEST_CASE("Simple Orderbook Bar Graph And Multi-Threading"){
    std::thread t1();   // call simpleBarGraph function in while loop
    fake::Order("MSFT", 80.03, 420, 0, 1);
    fake::Order("MSFT", 80.02, 310, 0, 1);
    fake::Order("MSFT", 81.0, 940, 0, 1);
    fake::Order("MSFT", 80.00, 50, 0, 1);
    fake::Order("MSFT", 79.99, 200, 1, 1);
    fake::Order("MSFT", 79.97, 400, 1, 1);
    fake::Order("MSFT", 79.98, 500, 1, 1);
    fake::Order("MSFT", 79.96, 800, 1, 1);
    fake::Order("MSFT", 79.9, 1200, 1, 1);
    auto start_time = std::chrono::high_resolution_clock::now();
    orderbook::displayGraph("MSFT");
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Program finished in " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " ms.\n";

    std::cout << "Program built and ran on " << currentDateTime() << ". \n";
}
