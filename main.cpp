/*  TODO
 * - finish making orderbook
 * - make a sample algorithm
 * - fake Stock object
 * - fix Limit/Stock circular refs?
 * - Rewrite Order so Order() is a function istead of a constructor?
 * - Make sure ticker is capitalized everywhere
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

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
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
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
    fake::Order fakeOrderGOOG102("Goog", 102, 200, 1, 1);

    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 1);
    fake::Order fakeOrderGOOG102Again("GoOg", 102, 100, 1, 1);
    fake::Order ("goog", 102, 100, 1, 1);    // anonymous; must save this in queue!

    CHECK(fake::Stock::stocks["GOOG"].limitsBid[10200].getSize() == 2); // line breaks if it's not caps

    CHECK(fakeOrderGOOG102.getTicker() == "GOOG");
    CHECK(fakeOrderGOOG102.getShares() == 200);
    CHECK(fakeOrderGOOG102.getLimitPrice() == 102);
    CHECK(fakeOrderGOOG102.isVisible() == 1);
    CHECK(fakeOrderGOOG102.isVisible() == true);
    CHECK(fakeOrderGOOG102Again.getOrderID() == 102);   // change this based on how many orders

    std::cout << "test" << std::endl;
    std::cout << "currentDateTime()=" << currentDateTime() << std::endl;
}
