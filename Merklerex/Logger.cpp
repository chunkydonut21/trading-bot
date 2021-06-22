//
//  Logger.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "Logger.hpp"
#include "CSVReader.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>



/** Logger constructor */
Logger::Logger() {

}

/** export the logbook data to a file */
void Logger::exportToFile() {
    
    // opens the file "log.csv"
    std::ofstream out("log.csv");
    
    std::cout << "[ExportToFile] Total transactions: " << logBook.size() << std::endl;
    
    // looping logbook and writing each log to the "log.csv" file
    for (std::string& line : logBook) {
        out << line;
    }
    
    // closes the file
    out.close();
}

/** insert the order in the logbook */
void Logger::logTransaction(OrderBookEntry order, bool marker) {
    
    // convert tokens to a string
    std::string line = CSVReader::tokensToString(order);
    
    if(marker) logBook.push_back("-------------------------- SALE --------------------------\n");
    
    // inserting string to the logbook
    logBook.push_back(line);
}

/** insert the wallet balance after each timestamp in the logbook */
void Logger::logWalletBalance(std::string wallet) {
    
    // insert wallet info to the logbook
    logBook.push_back("-------------------- WALLET BALANCE: --------------------\n" + wallet + "---------------------------------------------------------\n");
}
