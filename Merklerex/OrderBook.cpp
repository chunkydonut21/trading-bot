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
#include <set>

/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename){
    
    // read the csv and store the orders using map with key as timestamp and value
    // as vectors of orders in that timeframe
    orders = CSVReader::readCSV(filename);
    
}

 /** return vector of all known products in the database */
std::vector<std::string> OrderBook::getKnownProducts(std::string timestamp) {
    
    // create a set of product
    std::set<std::string> productSet;
    std::vector<std::string> products;

    // loop over the orders at a particular timestamp and get all products
    for (auto order : orders[timestamp]) {
        // check if the product is present in the productSet, if not then insert it
        productSet.insert(order.product);
    }

    // loop over the productSet and push the each product in the products array
    for (const auto& e : productSet) products.push_back(e);

    return products;
}


/** return vector of orders according to the sent filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType orderType, std::string product, std::string timestamp) {
    
    // vector of orders
    std::vector<OrderBookEntry> orders_sub;

    // loop over the orders at a particular timestamp and get all the orders
    // on the basis of product and product type
    for (OrderBookEntry& e: orders[timestamp]) {
        if (e.product == product && e.orderType == orderType) {
            orders_sub.push_back(e);
        }
    }

    return orders_sub;
}


/** return vector of orders acoording to the product and timestamp */
std::vector<OrderBookEntry> OrderBook::getAllOrders(std::string product, std::string timestamp) {
    
    // vector of orders
    std::vector<OrderBookEntry> orders_sub;
    
    // loop over the orders at a particular timestamp and get all the orders
    for (OrderBookEntry& e: orders[timestamp]) {
        if (e.product == product) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}



/** calculate the average price of the given order list */
double OrderBook::calculateAveragePrice(std::vector<OrderBookEntry> orderList) {
    double total = 0;
    
    // loop over the vecotr of orders and calculate the sum of prices
    for (OrderBookEntry const& orderbook : orderList) total = total + orderbook.price;
    
    // return the average of the prices
    return total / orderList.size();
}


/** retrieve the high price from the list of orders */
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orderList){
    double max = orderList[0].price;

    // loop over the vector of orders and update the max price
    for (OrderBookEntry const& order : orderList) {
        if(order.price > max) max = order.price;
    }

    return max;
}


/** retrieve the low price from the list of orders */
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orderList){
    double min = orderList[0].price;

    // loop over the vector of orders and update the min price
    for (OrderBookEntry const& order : orderList) {
        if(order.price < min) min = order.price;
    }

    return min;
}


/** returns the earliest time in the orderbook */
std::string OrderBook::getEarliestTime(){
    return orders.begin()->first;
}


/** returns the next time after the sent time in the orderbook */
std::string OrderBook::getNextTime(std::string timestamp) {
    
    std::string next_timestamp = "";
    
    // loop over the vector of orders to get the next timestamp
    for (const auto &order : orders) {
        if(order.first > timestamp) {
            next_timestamp = order.first;
            break;
        }
    }
    
    // if next timestamp is not found then assign next timestamp to the first value
    if(next_timestamp == "") next_timestamp = orders.begin()->first;
    
    return next_timestamp;
}


/** insert orders in the orderbook */
void OrderBook::insertOrder(OrderBookEntry& order) {
    
    // insert the order in the orders map for the given timestamp
    orders[order.timestamp].push_back(order);
}


/** matches asks to bids on the basis of product and timestamp and return the vector of orders */
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    
    // get all the ask orders for the given product and timestamp
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    
    // get all the bid orders for the given product and timestamp
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    
    // create a vector of sale orders
    std::vector<OrderBookEntry> sales;
    
    // check if the asks or bids are present
    if (asks.size() == 0 || bids.size() == 0) return sales;

    // sort asks lowest to highest
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    
    // sort bids highest to lowest
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    // loop over the ask and bids to find the match
    for (OrderBookEntry& ask : asks) {
        for (OrderBookEntry& bid : bids) {
            
            // if bid price is less than the ask price, exit the loop
            if (bid.price < ask.price) { break; }
            
            // if bid price is greater or equal to ask price, we found a match
            if(bid.price >= ask.price) {
                // create a orderbook entry object
                 OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::askSale};


                if(bid.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidSale;
                }

                if(ask.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::askSale;
                }


                // now work out how much was sold and
                // create new bids and asks covering
                // anything that was not sold
                // if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    // setting bid amount to 0 to make sure the bid is not processed again
                    bid.amount = 0;
                    // can do no more with this ask
                    // go onto the next ask
                    break;
                }
                // if bid amount > ask amount, then ask is completely gone slice the bid
                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    // we adjust the bid in place
                    // so it can be used to process the next ask
                    // ask.amount = ask.amount - bid.amount
                    bid.amount = bid.amount - ask.amount;
                    // ask is completely gone, so go to next ask
                    break;
                }
                
                // if bid amount is less than ask amount, bid is completely gone, slice the ask
                if (bid.amount < ask.amount && bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    // update the ask
                    // and allow further bids to process the remaining amount
                    // ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
                    // make sure the bid is not processed again
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    
    return sales;

}


/** removes simuser orders from the orderbook for a given timestamp */
void OrderBook::removeSimuserOrders(std::string &timestamp) {

    // loop over through the orders at a given timestamp and remove the orders placed by the simuser
    std::remove_if(orders[timestamp].begin(), orders[timestamp].end(), [&timestamp] (OrderBookEntry obe) {
        return obe.username == "simuser";
    });
}

