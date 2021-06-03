//
//  OrderBookEntry.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef OrderBookEntry_hpp
#define OrderBookEntry_hpp

#include <stdio.h>
#include <string>

enum class OrderBookType {bid, ask, unknown, sale};


class OrderBookEntry {
public:
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType);
    
    static OrderBookType stringToOrderBookType(std::string s);
    
    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);
    
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);
    
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);
    
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};


#endif /* OrderBookEntry_hpp */
