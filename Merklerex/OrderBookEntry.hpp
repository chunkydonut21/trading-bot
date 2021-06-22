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

//enum to store all order status
enum class OrderBookType {bid, ask, unknown, askSale, bidSale, offerWithdrawn};

class OrderBookEntry {
public:
    /** OrderbookEntry constructor */
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string _username = "dataset");

    /** convert string to orderbook type */
    static OrderBookType stringToOrderBookType(std::string s);
    /** compare timestamp between two orders */
    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);
    /** compare prices between two orders in the ascending order */
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);
    /** compare prices between two orders in the descending order */
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);
    /** convert order book type into string */
    static std::string orderBookTypeToString(OrderBookType type);
    
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};


#endif /* OrderBookEntry_hpp */
