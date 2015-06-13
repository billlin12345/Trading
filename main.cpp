/*  TODO
 * - finish making orderbook (initializing all the vars/selling/execution/canceling)
 * - fix Limit/Stock circular refs?
 * - Rewrite Order so Order() is a function istead of a constructor?
 * - Make sure ticker is converted to caps everywhere when used.
 * - Clean up all the include files in the headers.
 * - Add visibility condition.
 * - Unit test volume/size of Limit's and also the order queue.
 * - Refactor this awful code.
 */

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <time.h>

#include "curl/curl.h"
#include "catch.hpp"

#include "algorithms.hpp"
#include "fakeobj.hpp"
#include "orderbook.hpp"
#include "orderbooksimulation.hpp"
#include "transactioncostmodeling.hpp"
#include "webdata.hpp"

// Gets current date/time, format is YYYY-MM-DD.hppH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

TEST_CASE("Fake Stock"){
    std::srand(std::time(NULL));
    fake::Stock fakeStockDefault;
    fake::Stock fakeStockGOOG("Goog");

    CHECK(fakeStockDefault.getName() == "Apple");
    CHECK(fakeStockDefault.getCurrentPrice() < 150);

    CHECK(fakeStockGOOG.getName() == "GOOG Name");
    CHECK(fakeStockGOOG.getCurrentPrice() < 150);
}
// Order(std::string t, double price, double vol, int indi, bool visi);

TEST_CASE("Fake Order"){
    std::srand(std::time(NULL));
    fake::Order fakeOrderDefault;
    fake::Order fakeOrderGOOG102("GooG", 102, 200, 1, 1);   // order 101

    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 1);

    fake::Order ("GOOG", 102, 500, 1, 1);    // anonymous; must save this in queue!, order 102

    fake::Order fakeOrderGOOG102Again("GOog", 102, 100, 1, 1);  // order 103
    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 3);

    fake::Order z = fake::Order ("goog", 102, 10, 1, 0);    // order 104
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


    std::cout << "test" << std::endl;
    std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
}
