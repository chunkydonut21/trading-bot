//
//  MerkelMain.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 22/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "MerkelMain.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <vector>



MerkelMain::MerkelMain() {
    
}

void MerkelMain::init() {
    
    currentTime = orderbook.getEarliestTime();
        
    while (true) {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }
}

void MerkelMain::printMenu() {
    std::cout << "1: Print help!" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "Current Time is: " << currentTime << std::endl;
}

int MerkelMain::getUserOption() {
    std::string line;
    
    int userOption = 0;
    
    std::cout << "Type in 1-6" << std::endl;
    
    std::getline(std::cin, line);
    
    try {
         userOption = std::stoi(line);
    } catch (const std::exception& e) {
        
    }
    
    std::cout << "You choose: " << userOption << std::endl;
    
    return userOption;
}

void MerkelMain::printHelp() {
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats() {
    
    for (std::string const& p : orderbook.getKnownProducts()) {
        std::cout << "Products: " << p << std::endl;
        
        std::vector<OrderBookEntry> entries = orderbook.getOrders(OrderBookType::ask, p, currentTime);
        
        std::cout << "Asks Seen: " << entries.size() << std::endl;
        std::cout << "Max Ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min Ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
//    std::cout << "Market looks good: " << orders.size() << " entries" << std::endl;
//
//    unsigned int asks = 0;
//    unsigned int bids = 0;
//
//    for (const OrderBookEntry& order : orders) {
//        if(order.orderType == OrderBookType::ask) {
//            asks++;
//        } else if (order.orderType == OrderBookType::bid) {
//            bids++;
//        }
//    }
//
//    std::cout << "OrderBook asks: " << asks << " bids: " << bids << std::endl;

}

void MerkelMain::enterAsk() {
    std::cout << "Make an offer - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    
    std::string input;
        
    std::getline(std::cin, input);
    
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    if(tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk Bad Input" << tokens.size() << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            orderbook.insertOrder(obe);
            
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad Input: " << input << std::endl;
        }
    }
    std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid() {
    std::cout << "Make a bid - enter the amount." << std::endl;
}

void MerkelMain::printWallet() {
    std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next time frame." << std::endl;
    
    std::vector<OrderBookEntry> sales = orderbook.matchAsksToBids("ETH/BTC", currentTime);
    
    std::cout << "Sales: " << sales.size() << std::endl;
    
    for (OrderBookEntry& sale : sales) {
        std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
    }
    
    currentTime = orderbook.getNextTime(currentTime);
    
//    2020/03/17 17:01:24,ETH/BTC,bid,13,0.5
//    2020/03/17 17:01:24,ETH/BTC,ask,13,0.5

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
