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
