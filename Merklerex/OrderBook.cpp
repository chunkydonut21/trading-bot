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



void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);
    
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}



std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    
    std::vector<OrderBookEntry> sales;
    
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    
    
    for (OrderBookEntry& ask : asks) {
        for (OrderBookEntry& bid : bids) {
            if(bid.price >= ask.price) {
                
                 OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::askSale};
                
                if(bid.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidSale;
                }
                
                if(ask.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::askSale;
                }
               
                
                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                } else if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                else if (bid.amount < ask.amount && bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
                
            }
        }
    }
    
    
    return sales;

}
