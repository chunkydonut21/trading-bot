//
//  TradingBot.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef Bot_hpp
#define Bot_hpp

#include <stdio.h>
#import "OrderBookEntry.hpp"
#import "MerkelMain.hpp"
#include <vector>
#include <map>
#import "ProductTracker.hpp"


/** TradingBot extends MerkelMain */
class TradingBot : MerkelMain {
public:
    /** Trading bot constructor*/
    TradingBot();
    /** initialize bot */
    void initBot(bool bot);
    
private:
    /** intialize the product tracker */
    void initializeProductTracker();
    /** run bot and automate the trade  */
    void automateBot();
    /** vector of product tracker which contains information on predicted prices */
    std::vector<ProductTracker> productTracker;
    /** processing the sale */
    void processSale(OrderBookEntry& obe);
    /** check whether if it is right time to trade */
    bool lookForTrade(ProductTracker& product);
    /** calculate the prediction price and check whether to ask or sale */
    OrderBookEntry makePrediction(ProductTracker& proudct);
    
};




#endif /* Bot_hpp */


