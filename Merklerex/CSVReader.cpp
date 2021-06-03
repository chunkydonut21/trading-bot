//
//  CSVReader.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 10/05/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "CSVReader.hpp"
#include "OrderBookEntry.hpp"
#include <iostream>
#include <fstream>


std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {
    std::vector<OrderBookEntry> entries;
    
    std::ifstream csvFile{csvFilename};
    
    std::string line;
    
    if (!csvFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
        exit(-1);
    }
    
    
    while (std::getline(csvFile, line)) {
        try {
            OrderBookEntry obe = stringToOBE(tokenise(line, ','));
            entries.push_back(obe);
        } catch (const std::exception& e) {
            std::cout << "Bad Data" << std::endl;
        }
    }
    
    std::cout << "Total entries read: " << entries.size() << std::endl;
    
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string line, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
  
    start = line.find_first_not_of(separator, 0);
    
    do {
        std::string token;
        end = line.find_first_of(separator, start);
        
        if (start == line.length() || start == end) break;
        
        if (end >= 0) token = line.substr(start, end - start);
        else token = line.substr(start, line.length() - start);
        
        tokens.push_back(token);
        start = end + 1;
        
    } while(end > 0);
    
    return tokens;

}

OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens) {
    
    double amount;
    double price;
    
    
    if (tokens.size() != 5) {
        std::cout << "CSVReader::stringToOBE Bad line" << std::endl;
        throw std::exception{};
    }
    
    try {
        amount = std::stod(tokens[4]);
        price = std::stod(tokens[3]);
        
    } catch(const std::exception& e) {
        std::cout << "CSVReader::stringToOBE Bad float!" << std::endl;
        throw;
        
    }
    
    OrderBookEntry entry{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
        
    return entry;
}


OrderBookEntry CSVReader::stringToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderType) {
    
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    } catch (const std::exception& e) {
        std::cout << "CSVReader::stringToOBE Bad float: " << priceString << std::endl;
        std::cout << "CSVReader::stringToOBE Bad float: " << amountString << std::endl;
        throw;
    }
    
    OrderBookEntry entry{price, amount, timestamp, product, orderType};
    return entry;
}
