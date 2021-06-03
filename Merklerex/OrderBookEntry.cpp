//
//  OrderBookEntry.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "OrderBookEntry.hpp"


OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType):
price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType) {}



OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
    if(s == "ask") {
        return OrderBookType::ask;
    } else if (s == "bid") {
        return OrderBookType::bid;
    }
    
    return OrderBookType::unknown;
}


bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price < e2.price;
    
}
    
bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price > e2.price;
}

