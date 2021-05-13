//
//  MerkelMain.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef MerkelMain_hpp
#define MerkelMain_hpp

#include <stdio.h>
#include <vector>
#include "OrderBookEntry.hpp"
#include "OrderBook.hpp"

class MerkelMain {
public:
    MerkelMain();
    /** call this to start the sim */
    void init();
private:
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void processUserOption(int userOption);
    OrderBook orderbook{"data.csv"};
    
    std::string currentTime;
};

#endif /* MerkelMain_hpp */
