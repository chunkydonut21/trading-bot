//
//  OrderBook.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 12/05/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "OrderBook.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <vector>
#include <map>



OrderBook::OrderBook(std::string filename){
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& order : orders) {
        prodMap[order.product] = true;
    }


    for (auto const& e : prodMap) {
        products.push_back(e.first);
    }
    
    return products;
    
}


std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType orderType, std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    
    for (OrderBookEntry& e: orders) {
        if (e.orderType == orderType && e.product == product && e.timestamp == timestamp) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    
    for (OrderBookEntry const& order : orders) {
        if(order.price > max) max = order.price;
    }
    
    return max;
}


double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    
    for (OrderBookEntry const& order : orders) {
        if(order.price < min) min = order.price;
    }
    
    return min;
}


std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}


std::string OrderBook::getNextTime(std::string timestamp) {
    
    std::string next_timestamp = "";
    
    for (OrderBookEntry const& order : orders) {
        if(order.timestamp > timestamp) {
            next_timestamp = order.timestamp;
            break;
        }
    }
    
    if(next_timestamp == "") next_timestamp = orders[0].timestamp;
    
    return next_timestamp;
}

