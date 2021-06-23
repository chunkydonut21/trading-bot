//
//  MerkelMain.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "MerkelMain.hpp"
#include <iostream>

/** Merkelmain constructor */
MerkelMain::MerkelMain() {
    
}

/** call this to start the sim */
void MerkelMain::init(bool bot) {
    
    // get the earliest time from the orderbook and assign it to the current time
    currentTime = orderbook.getEarliestTime();
    
    // insert currency to the wallet
    // bot will use these currencies to automate trade
    wallet.insertCurrency("BTC", 1000);
    wallet.insertCurrency("ETH", 1000);
    wallet.insertCurrency("DOGE", 1000);
    wallet.insertCurrency("USDT", 1000);
    
    // check if the bot paramter is true or false
    // if it is false then run the manual trading process
    if(!bot) {
        while (true) {
            // print the menu
            printMenu();
            // store user option selected by user
            int userOption = getUserOption();
            // process user option
            processUserOption(userOption);
        }
    }
}

 /** prints the menu*/
void MerkelMain::printMenu() {
    std::cout << "1: Print help!" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "Current Time is: " << currentTime << std::endl;
}

/** get the user options */
int MerkelMain::getUserOption() {
    std::string line;
    
    int userOption = 0;
    
    std::cout << "Type in 1-6" << std::endl;
    
    // read the input user entered
    std::getline(std::cin, line);
    
    try {
        // convert user option stored in string line to integer
         userOption = std::stoi(line);
    } catch (const std::exception& e) {
        
    }
    
    std::cout << "You choose: " << userOption << std::endl;
    
    return userOption;
}

/** print help */
void MerkelMain::printHelp() {
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

/** print market stats */
void MerkelMain::printMarketStats() {
    
    for (std::string const& p : orderbook.getKnownProducts(currentTime)) {
        std::cout << "Products: " << p << std::endl;
        
        std::vector<OrderBookEntry> askEntries = orderbook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> bidEntries = orderbook.getOrders(OrderBookType::bid, p, currentTime);
        
        std::cout << "Asks Seen: " << askEntries.size() << std::endl;
        std::cout << "Bids Seen: " << bidEntries.size() << std::endl;
        
        std::cout << "Max Ask: " << OrderBook::getHighPrice(askEntries) << std::endl;
        std::cout << "Min Ask: " << OrderBook::getLowPrice(askEntries) << std::endl;

        std::cout << "Max Bid: " << OrderBook::getHighPrice(bidEntries) << std::endl;
        std::cout << "Min Bid: " << OrderBook::getLowPrice(bidEntries) << std::endl;
        
    }
}

/** takes the user ask input */
void MerkelMain::enterAsk() {
    std::cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    
    std::string input;
        
    std::getline(std::cin, input);
    
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    if(tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk Bad Input" << tokens.size() << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderbook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficent funds." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad Input: " << input << std::endl;
        }
    }
    
    std::cout << "You typed: " << input << std::endl;
}


/** takes the user bid input */
void MerkelMain::enterBid() {
    std::cout << "Make a bid - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    
    std::string input;
        
    std::getline(std::cin, input);
    
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    if(tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid Bad Input" << tokens.size() << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderbook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficent funds." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid Bad Input: " << input << std::endl;
        }
    }
    std::cout << "You typed: " << input << std::endl;}


/** print wallet */
void MerkelMain::printWallet() {
    std::cout << wallet.toString()<< std::endl;
}


/** moving to the next time frame */
void MerkelMain::gotoNextTimeframe() {
    
    std::cout << "Going to next time frame." << std::endl;
    
    // loop through each of the products for the current time
    for (std::string& product : orderbook.getKnownProducts(currentTime)) {
        // match asks and bids on the basis of a particular product at the current time
        // and returns the vector of sale order generated
        std::vector<OrderBookEntry> sales = orderbook.matchAsksToBids(product, currentTime);
        
        // check how many sales were generated for a particular product at the current time
        std::cout << "There was : " << sales.size() << " number of sales" << std::endl;
        
        
        // loop through the vector of sales
        for (OrderBookEntry& sale : sales) {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            // check if the sale is made by simuser
            if (sale.username == "simuser") {
                // process sale and update wallet
                wallet.processSale(sale);
                // log the transactions in the logger instance
                logger.logTransaction(sale, true);
            }
        }
    }
    
    // change the current timeframe to the next timeframe
    currentTime = orderbook.getNextTime(currentTime);
    
    // withdraw non fulfilled orders by the simuser
    withdrawOffers(currentTime);
    
    // add wallet balance to the logger
    logger.logWalletBalance(wallet.toString());
    
    // export logger data to the log file
    logger.exportToFile();
    
}


/** process user option choosen by user */
void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0) {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    
    if (userOption == 1) {
        printHelp();
    }

    if (userOption == 2) {
        printMarketStats();
    }
    
    if (userOption == 3) {
        enterAsk();
    }
    
    if (userOption == 4) {
        enterBid();
    }
    
    if (userOption == 5) {
        printWallet();
    }
    
    if (userOption == 6) {
        gotoNextTimeframe();
    }
}


/** make ask generated by the bot to the exchange */
void MerkelMain::makeAsk(OrderBookEntry& obe) {
    try {
        obe.username="simuser";
        // check if wallet can fulfill order
        if (wallet.canFulfillOrder(obe)) {
            std::cout << "Wallet looks good. " << std::endl;
            // if wallet can fulfill order insert order to the orderbook
            orderbook.insertOrder(obe);
            // insert the transaction to the logger
            logger.logTransaction(obe);
        }
        else {
            std::cout << "not enough money. " << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
    }
}


/** make bid generated by the bot to the exchange */
void MerkelMain::makeBid(OrderBookEntry& obe) {
    try {
        obe.username="simuser";
        // check if wallet can fulfill order
        if (wallet.canFulfillOrder(obe)) {
            // if wallet can fulfill order insert order to the orderbook
            std::cout << "Wallet looks good. " << std::endl;
            orderbook.insertOrder(obe);
            // insert the transaction to the logger
            logger.logTransaction(obe);
        }
        else {
            std::cout << "not enough money. " << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
    }
}


/** process user option choosen by user */
void MerkelMain::withdrawOffers(std::string timestamp) {
    
    // remove asks or bids placed by user at a timeframe
    orderbook.removeSimuserOrders(timestamp);
}
