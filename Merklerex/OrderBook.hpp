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

class OrderBook {
public:
    /**
     construct, reading a csv data file
     */
    OrderBook(std::string filename);
    
    
    /**
        return vector of all known products in the database
     */
    std::vector<std::string> getKnownProducts();
    
    /**
        return vector of orders according to the sent filters
     */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    
    /**
        returns the earliest time in the orderbook
     */
    std::string getEarliestTime();
    
    /**
        returns the next time after the sent time in the orderbook
     */
    std::string getNextTime(std::string timestamp);
    
    void insertOrder(OrderBookEntry& order);
    
    
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    
private:
    std::vector<OrderBookEntry> orders;
};

#endif /* OrderBook_hpp */
