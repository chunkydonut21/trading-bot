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
#include "CSVReader.hpp"
#include "Wallet.hpp"

#include <filesystem>

int main() {
    
    MerkelMain app{};
    app.init();
    
//    CSVReader::readCSV("data.csv");
//
//    Wallet wallet;
//    wallet.insertCurrency("BTC", 10000);
//    wallet.insertCurrency("USDT", 1000);
//    std::cout << "Wallet has BTC " << wallet.containsCurrency("BTC", 10) << std::endl;
//    std::cout << wallet.toString() << std::endl;
//    wallet.removeCurrency("BTC", 1000);
//    std::cout << wallet.toString() << std::endl;
 
    return 0;
}
