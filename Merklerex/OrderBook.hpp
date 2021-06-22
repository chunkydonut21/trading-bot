//
//  OrderBook.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 12/05/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef OrderBook_hpp
#define OrderBook_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "OrderBookEntry.hpp"
#include <map>

#include <unordered_map>

class OrderBook {
public:
    /** construct, reading a csv data file */
    OrderBook(std::string filename);
    
    /** return vector of all known products in the database */
    std::vector<std::string> getKnownProducts(std::string timestamp);
    
    /** return vector of orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    
    /** return vector of orders acoording to the product and timestamp */
    std::vector<OrderBookEntry> getAllOrders(std::string product, std::string timestamp);
    
    /** calculate the average price of the given order list */
    double calculateAveragePrice(std::vector<OrderBookEntry> orderList);
    
    /** returns the earliest time in the orderbook */
    std::string getEarliestTime();
    
    /** returns the next time after the sent time in the orderbook */
    std::string getNextTime(std::string timestamp);
    
    /** insert orders in the orderbook */
    void insertOrder(OrderBookEntry& order);
    
    /** retrieve the high price from the list of orders */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    
    /** retrieve the low price from the list of orders */
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    
    /** matches asks to bids on the basis of product and timestamp and return the vector of orders */
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    
    /** removes simuser orders from the orderbook for a given timestamp */
    void removeSimuserOrders(std::string &timestamp);
    
private:

    /** map of timestamp as a key and orders as the value */
    std::map<std::string, std::vector<OrderBookEntry>> orders;
};

#endif /* OrderBook_hpp */
