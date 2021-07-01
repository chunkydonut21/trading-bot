//
//  TradingBot.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "TradingBot.hpp"
#include <iostream>
#include <math.h>


/** trading bot constructor */
TradingBot::TradingBot() {}

/** initialize bot */
void TradingBot::initBot(bool bot){
    
    // initialize merkelmain and pass the boolean bot parameter to check whether to run bot or not
    init(bot);
    
    std::cout << "[TradingBot::initBot] Merklebot has been initialized. The bot will now run the simulation." << std::endl;
       
    // initialize the product tracker to store average prices
    initializeProductTracker();
    
    // run bot and automate the trade
    automateBot();
}

/** intialize the product tracker */
void TradingBot::initializeProductTracker() {
    
    // get all known products from the orderbook and store them in vector of strings
    std::vector<std::string> products = orderbook.getKnownProducts(currentTime);
    
    // loop over the vector of products
    for (std::string product : products) {
        
        // initialize the product tracker with product, prices as empty vector, slope as 0 and constant as 0
        ProductTracker tracker{product, {}, 0, 0};
        // push the initialized tracker to the vector of product tracker
        productTracker.push_back(tracker);
    }
}

/** run bot and automate the trade  */
void TradingBot::automateBot() {
    
    // store the current time as start time
    std::string startTime = currentTime;
    
    // run the do while loop and stop it when the start time is equal to the current time
    // which shows that we have run the bot for all timestamps
    do {
        // loop over the product tracker instances we created for all product
        for (ProductTracker& product : productTracker) {
            
            // check if it is right time to trade
            bool shouldBotTrade = lookForTrade(product);
            
            // if it is right time to trade then make prediction whether to ask or sale
            if (shouldBotTrade) {
                // store the predicted object into the OrderBookEntry object
                OrderBookEntry obe = makePrediction(product);
                // process sale
                processSale(obe);
            }
        }
        
        // go to next time frame and repeat the process till we have covered all the timeframes
        gotoNextTimeframe();
        
    } while (currentTime != startTime);
}


/** check whether if it is right time to trade */
bool TradingBot::lookForTrade(ProductTracker& product) {
    
    // get all the orders on the basis of product name and current time and store in vector of orders
    std::vector<OrderBookEntry> orders = orderbook.getAllOrders(product.name, currentTime);
    
    // trade is not possible if the orders are not present
    if(orders.size() < 1) {
        return false;
    }

    // calculate the average price of orders
    double average = orderbook.calculateAveragePrice(orders);
    // insert the average price in the price array of product tracker object
    product.price.push_back(average);
    // calculate the size of price array
    long n = product.price.size();
    
    // a = slope of the line
    // b = constant (y-intercept of the line of best fit)
    double a, b;
    
    std::vector<double> y_axis_value = product.price;
    
    
    double x_sum = 0, x_sum_2 = 0, y_sum = 0, xy_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        x_sum = x_sum + i;
        y_sum = y_sum + y_axis_value[i];
        x_sum_2 = x_sum_2 + pow(i, 2);
        xy_sum = xy_sum + i * y_axis_value[i];
    }
    
    
    // calculating the slope
    a = ((n * xy_sum) - (x_sum * y_sum)) / ((n * x_sum_2) - (x_sum * x_sum));
    
    // calculate the constat (y-intercept of the line of best fit)
    b = (y_sum/n) - ((a * x_sum)/n);

    // update the product tracker object with slope and intercept which we calculated
    product.a = a;
    product.b = b;
    
    std::cout<<"[TradingBot::lookForTrade] The linear fit line is: "<<a<<"x + "<<b<<std::endl;
    
    // if the trade is possible
    return true;

}

/** calculate the prediction price and check whether to ask or sale */
OrderBookEntry TradingBot::makePrediction(ProductTracker& product) {

    // assign ordertype as ask as default
    OrderBookType orderType = OrderBookType::ask;
    
    // if the slope of the product is less than 0 which means the price
    // is low and it is the good time to buy the product
    if (product.a < 0) orderType = OrderBookType::bid;
    
    // if the slope of the product is greater than 0 which means the price
    // is high and it is the good time to sell the product
    if (product.a > 0) orderType = OrderBookType::ask;
    
    // calculate the sale price to put on the exchange using
    // the line of best fit y = ax + b
    double salePrice = product.a * product.price.size() + product.b;

    // initialize the sale object
    OrderBookEntry sale{salePrice, 1.0, currentTime, product.name, orderType};
    
    // return the sale object
    return sale;
}

/** processing the sale */
void TradingBot::processSale(OrderBookEntry& obe){

    
    // check if the ordertype is bid or ask
    if(obe.orderType == OrderBookType::bid) {
        
        std::cout << "[TradingBot::processSale] Bot is now making Bid" << std::endl;
        // make bid to the exchange
        makeBid(obe);

    } else if (obe.orderType == OrderBookType::ask) {
        std::cout << "[TradingBot::processSale] Bot is now making Ask" << std::endl;
        // make ask to the exchange
        makeAsk(obe);
    }
}
