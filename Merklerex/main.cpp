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

#include "OrderBookEntry.hpp"
#include "MerkelMain.hpp"

int main() {
    
//    std::vector<OrderBookEntry> orders;
//
//
//    orders.push_back(OrderBookEntry(5000.3342, 0.024152, "2020/03/17 17:01:24.886382", "BTC/USDT", OrderBookType::bid));
//
//    for (OrderBookEntry& order : orders) {
//        std::cout << "The price is " << order.price << std::endl;
//    }
//
//    for (unsigned int i = 0; i < orders.size(); ++i) {
//        std::cout << "The price is " << orders[i].price << std::endl;
//    }
//
//    while (true) {
//
//        printMenu();
//
//        int userOption = getUserOption();
//
//        processUserOption(userOption);
//
//    }
    
    MerkelMain app{};
    app.init();
    
    
    return 0;
}
