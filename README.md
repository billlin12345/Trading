# Trading
I am slowly porting over from Python to C++. For a synopsis of the Python implementation/goals:
https://dl.dropboxusercontent.com/u/94871865/Project%20Synopsis.docx


This is an algorithmic trading platform that will allow for backtesting, portfolio optimization, and limit orderbook simulations.

The orderbook has O(1) efficiency in saving an order, canceling an order, and executing an order:

Example order:
Order("GOOG", 536, 150, 1, 1) is buying 150 shares of Google stock at price 536 visibly in the orderbook.

Each order is stored in a deque of orders which is stored in a vector of limit prices which is in a map of stocks.

