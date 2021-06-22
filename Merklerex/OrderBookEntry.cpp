//
//  OrderBookEntry.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "OrderBookEntry.hpp"


/** OrderbookEntry constructor */
OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string _username):
price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType), username(_username) {}


/** convert string to orderbook type */
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
    if(s == "ask") {
        return OrderBookType::ask;
    } else if (s == "bid") {
        return OrderBookType::bid;
    }
    
    return OrderBookType::unknown;
}

/** compare timestamp between two orders */
bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.timestamp < e2.timestamp;
}

/** compare prices between two orders in the ascending order */
bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price < e2.price;
    
}
 
/** compare prices between two orders in the descending order */
bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price > e2.price;
}

/** convert order book type into string */
std::string OrderBookEntry::orderBookTypeToString(OrderBookType type) {
    if(type == OrderBookType::ask) {
        return "ASK";
    } else if (type == OrderBookType::bid) {
        return "BID";
    } else if (type == OrderBookType::askSale) {
        return "ASK_SALE";
    } else if (type == OrderBookType::bidSale) {
        return "BID_SALE";
    } else if (type == OrderBookType::offerWithdrawn) {
        return "OFFER_WITHDRAWN";
    }

    return "UNKNOWN";
}
