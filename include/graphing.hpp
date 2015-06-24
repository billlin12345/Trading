#ifndef GRAPHING
#define GRAPHING

#include <map>
#include <string>
#include "fakeobj.hpp"

namespace orderbook{

void displayGraph(std::string ticker);
void updateGraph(fake::Order order);
}

#endif // GRAPHING

