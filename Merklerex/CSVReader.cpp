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


/** reads a csv file and returns the map with key as timestamps and value as vector of orders */
std::map<std::string, std::vector<OrderBookEntry>> CSVReader::readCSV(std::string csvFilename) {

    // initialize a map with key as timestamp and value as vector of orders
    std::map<std::string, std::vector<OrderBookEntry>> entries;
    // open the csvfile
    std::ifstream csvFile{csvFilename};

    // initialize a string which will store each line of the csv file
    std::string line;

    // check if csv file cannot be opened
    if (!csvFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
        exit(-1);
    }

    
    // while loop until there is a line to read from csv file
    while (std::getline(csvFile, line)) {
        try {
            // convert string to orderbookentry object with ',' as separator
            OrderBookEntry obe = stringToOBE(tokenise(line, ','));
            // push the order in the entries map on the basis of timestamp
            entries[obe.timestamp].push_back(obe);
        } catch (const std::exception& e) {
            std::cout << "Bad Data" << std::endl;
        }
    }

    std::cout << "Total entries read: " << entries.size() << std::endl;

    return entries;
}

/** convert the string to a vector of strings using a separator character */
std::vector<std::string> CSVReader::tokenise(std::string line, char separator) {
    // initialize a vector of tokens
    std::vector<std::string> tokens;
    // initialize start and end as signed integer
    signed int start, end;
  
    // tokenise the line
    start = int (line.find_first_not_of(separator, 0));
    
    do {
        std::string token;
        end = int (line.find_first_of(separator, start));
        
        if (start == line.length() || start == end) break;
        
        if (end >= 0) token = line.substr(start, end - start);
        else token = line.substr(start, line.length() - start);
        
        tokens.push_back(token);
        start = end + 1;
        
    } while(end > 0);
    
    return tokens;

}

/** convert string to order book entry */
OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens) {
    
    // initialize amount and price
    double amount, price;
    
    // check if the token size is less than 5
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
    
    // initialize a orderbookentry object
    OrderBookEntry entry{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
        
    return entry;
}

/** convert string to order book entry*/
OrderBookEntry CSVReader::stringToOBE(std::string priceString, std::string amountString, std::string timestamp,
                                      std::string product, OrderBookType orderType) {
    
    double price, amount;
    
    try {
        // convert price from string to double
        price = std::stod(priceString);
        // convert amount from string to double
        amount = std::stod(amountString);
    } catch (const std::exception& e) {
        std::cout << "CSVReader::stringToOBE Bad float: " << priceString << std::endl;
        std::cout << "CSVReader::stringToOBE Bad float: " << amountString << std::endl;
        throw;
    }
    
    // initialize a orderbookentry object
    OrderBookEntry entry{price, amount, timestamp, product, orderType};
    return entry;
}

/** convert a obe to a string */
std::string CSVReader::tokensToString(OrderBookEntry order) {
    std::string line;
    
    line = order.timestamp + "," + OrderBookEntry::orderBookTypeToString(order.orderType) + "," + order.product + "," + std::to_string(order.price) + "," + std::to_string(order.amount) + "\n";
    return line;
}

