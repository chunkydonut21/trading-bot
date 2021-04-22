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

enum class OrderBookType {bid, ask};


class OrderBookEntry {
public:
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType);
    
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};


#endif /* OrderBookEntry_hpp */
