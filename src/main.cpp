/*  TODO
 * - finish making orderbook (initializing all the vars/selling/execution/canceling)
 * - Clean up all the include files in the headers.
 * - Add visibility condition.
 * - graphing: consider volume not divisible by 10
 *     - set * to 100 ? what about closer to the bid/ask
 *     - change to a graphing library
 * - What is being affected by precision(2) after drawing the orderbook? rounding problems??
 ** - Use built-in deque size or use the one I manually define and increment in Limit?
 */

/* Possible bugs/issues:
 * fake::Order z = fake::Order breaks bestAsk/bestBid (constructor?)
 *  graph is missing 79.99.... gets combined with 79.98 instead.
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
#include "../include/helperfunctions.hpp"
#include "../include/graphing.hpp"
#include "../include/orderbook.hpp"
#include "../include/orderbooksimulation.hpp"
#include "../include/transactioncostmodeling.hpp"
#include "../include/webdata.hpp"
#include "../cointegration/JohansenHelper.h"

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

TEST_CASE("Simple Orderbook Bar Graph (And Multi-Threading Later)"){
    std::thread t1();   // call simpleBarGraph function in while loop
    fake::Order("MSFT", 80.04, 940, 0, 1);
    fake::Order("MSFT", 80.03, 420, 0, 1);
    fake::Order("MSFT", 80.02, 310, 0, 1);
    fake::Order("MSFT", 80.01, 90, 0, 1);

    fake::Order("MSFT", 79.99, 200, 1, 1);
    fake::Order("MSFT", 79.98, 300, 1, 1);
    fake::Order("MSFT", 79.97, 500, 1, 1);
    fake::Order("MSFT", 79.96, 800, 1, 1);
    fake::Order("MSFT", 79.9, 1200, 1, 1);

//    auto start_time = std::chrono::high_resolution_clock::now();
//    orderbook::displayGraph("MSFT");
//    auto end_time = std::chrono::high_resolution_clock::now();
//    std::cout << "Program finished in " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " ms.\n";

}


TEST_CASE("Buys and Sells Along the Order Deque"){
    fake::Order("SAR", 81, 150, 1, 1);
    fake::Order("SAR", 81, 350, 1, 1);
    fake::Order("SAR", 81, 50, 1, 1);
    fake::Order("SAR", 81, 550, 1, 1);
    fake::Order("SAR", 81, 150, 1, 1);

    fake::Order("SAR", 81, 150, 0, 1);
    fake::Order("SAR", 81, 350, 0, 1);
    fake::Order("SAR", 81, 50, 0, 1);
    fake::Order("SAR", 81, 550, 0, 1);
    fake::Order("SAR", 81, 150, 0, 1);

    std::cout <<"Before executing any orders: \n";
    orderbook::displayGraph("SAR");

    CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].orders.size() == 5);
    CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].getVolume() == 1250);
    CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].getSize() == 5);

    fake::Order("SAR", 100, 1);  // take partial
    fake::Order("SAR", 50, 1);  // take exactly to finish
    fake::Order("SAR", 700, 1); // take over
    fake::Order("SAR", 2500, 1);  // take too much that there isn't any remaining
// last order didn't go through because it's not done implementation yet.

    std::cout <<"After executing the orders: \n";
    orderbook::displayGraph("SAR");

    std::cout << "Program built and ran on " << helper::getCurrentDateTime() << ". \n";

  //  CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].orders.size() == 0);
  //  CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].getVolume() == 0);
  //  CHECK(fake::Stock::stocks["SAR"].limitsAsk[fake::Stock::stocks["SAR"].bestAsk * 100].getSize() == 0);


//    fake::Order("SAR", 100, 0);  // take partial
/*  fake::Order("SAR", 50, 0);  // take exactly to finish
    fake::Order("SAR", 700, 0); // take over
    fake::Order("SAR", 2500, 0);   // take too much that there isn't any remaining
*/
}







/*
TEST_CASE("Buys and Sells Along Prices"){
    fake::Order("KAR", 81.0, 940, 0, 1);
    fake::Order("KAR", 80.03, 420, 0, 1);
    fake::Order("KAR", 80.02, 310, 0, 1);
    fake::Order("KAR", 80.00, 90, 0, 1);

    fake::Order("KAR", 79.99, 200, 1, 1);
    fake::Order("KAR", 79.97, 400, 1, 1);
    fake::Order("KAR", 79.98, 500, 1, 1);
    fake::Order("KAR", 79.96, 800, 1, 1);
    fake::Order("KAR", 79.9, 1200, 1, 1);

    fake::Order("KAR", 40, 1);  // take partial
    fake::Order("KAR", 50, 1);  // take exactly to finish
    fake::Order("KAR", 400, 1); // take over
    fake::Order("KAR", 2500, 1);   // take too much that there isn't any remaining

    fake::Order("KAR", 100, 0);  // take partial
    fake::Order("KAR", 100, 0);  // take exactly to finish
    fake::Order("KAR", 500, 0); // take over
    fake::Order("KAR", 3500, 0);   // take too much that there isn't any remaining
}
*/
