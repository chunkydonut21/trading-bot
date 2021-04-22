//
//  MerkelMain.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "MerkelMain.hpp"
#include <iostream>
#include <vector>



MerkelMain::MerkelMain() {
    
}

void MerkelMain::init() {
    
    loadOrderBook();
    
    while (true) {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }
}

void MerkelMain::loadOrderBook() {
    
    orders.push_back(OrderBookEntry(5000.3342, 0.024152, "2020/03/17 17:01:24.886382", "BTC/USDT", OrderBookType::bid));
}


void MerkelMain::printMenu() {
    std::cout << "1: Print help!" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int MerkelMain::getUserOption() {
    int userOption;
    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You choose: " << userOption << std::endl;
    
    return userOption;
}

void MerkelMain::printHelp() {
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats() {
    std::cout << "Market looks good: " << orders.size() << " entries" << std::endl;
}

void MerkelMain::enterOffer() {
    std::cout << "Make an offer - enter the amount." << std::endl;
}

void MerkelMain::enterBid() {
    std::cout << "Make a bid - enter the amount." << std::endl;
}

void MerkelMain::printWallet() {
    std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next time frame." << std::endl;
}

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
        enterOffer();
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
