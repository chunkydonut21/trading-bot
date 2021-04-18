//
//  main.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 12/04/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>


enum class OrderBookType {bid, ask};



void printMenu() {
    std::cout << "1: Print help!" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int getUserOption() {
    int userOption;
    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You choose: " << userOption << std::endl;
    
    return userOption;
}

void printHelp() {
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void printMarketStats() {
    std::cout << "Market looks good" << std::endl;
}

void enterOffer() {
    std::cout << "Make an offer - enter the amount." << std::endl;
}

void enterBid() {
    std::cout << "Make a bid - enter the amount." << std::endl;
}

void printWallet() {
    std::cout << "Your wallet is empty." << std::endl;
}

void gotoNextTimeframe() {
    std::cout << "Going to next time frame." << std::endl;
}

void processUserOption(int userOption) {
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

int main() {
    
    
    std::string timestamp{"2020/03/17 17:01:24.886382"};
    std::string product{"BTC/USDT"};
    

//    OrderBookType orderType = OrderBookType::bid;
    
    std::vector<double> prices;
    std::vector<double> amounts;
    std::vector<std::string> timestamps;
    std::vector<std::string> products;
    std::vector<OrderBookType> orderTypes;
    
    prices.push_back(5000.3342);
    amounts.push_back(0.024152);
    timestamps.push_back("2020/03/17 17:01:24.886382");
    products.push_back("BTC/USDT");
    orderTypes.push_back(OrderBookType::bid);
    
    
    while (true) {
        
        printMenu();
        
        int userOption = getUserOption();
        
        processUserOption(userOption);
        
    }
    
    
    return 0;
}
