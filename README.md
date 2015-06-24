# Trading
Testing Github functionalities.

Slowly porting over from Python to C++. 

This is an algorithmic trading platform that will allow for backtesting, portfolio optimization, and limit orderbook simulations.

The orderbook has O(1) efficiency in saving an order, canceling an order, and executing an order:

Example order:
Order("GOOG", 536, 150, 1, 1) is buying 150 shares of Google stock at price 536 visibly.

Each order is stored in a deque of orders which is stored in a vector of limit prices which is in a vector of stocks.

