//  main.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 12/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include "Wallet.hpp"
#include "TradingBot.hpp"

#include <filesystem>
#include <chrono>


void runTradeBot()
{
    /* Initialize the TradingBot class instance. */
    TradingBot tradingBot{};
    
    // calling initBot with paramter as true to run bot
    tradingBot.initBot(true);
    
}

int main() {
    
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto time1 = high_resolution_clock::now();
    
    runTradeBot();
    
    auto time2 = high_resolution_clock::now();

    /* Getting number of seconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(time2 - time1);

    std::cout << ms_int.count() << "ms " << "is the total time taken to load the CSV & execute the trade.\n";
 
    return 0;
}
