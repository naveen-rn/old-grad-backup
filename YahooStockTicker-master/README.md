YahooStockTicker
================

A web based program to obtain the stock values of all the Stock IDs provided. 
This is done using the Yahoo Stock details query


A program that will help to view the net asset value of shares held by a user.
The program will read a list of stock ticket symbols and number of shares for each ticker.
It will then go out to Yahoo! and request for the current stock price for each symbol.
The program will then find the values for a stock held by the user based on the current
stock price and the number of shares held.

The program will display the following:

A table with each line displaying a ticker symbol, number of shares for that ticket, and the 
total value for that stock ticker.
In the last row, display the net asset value which is a total of the values for all the stocks held.

To requests for the current stock price from Yahoo!, use the URL
http://ichart.finance.yahoo.com/table.csv?s=TICKER

where TICKER is a symbol like GOOG or AAPL.
