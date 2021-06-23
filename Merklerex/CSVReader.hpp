//
//  CSVReader.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 10/05/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef CSVReader_hpp
#define CSVReader_hpp
#import "OrderBookEntry.hpp"
#import <vector>
#include <stdio.h>
#include <map>


class CSVReader {
public:
    CSVReader();
    
    /** reads a csv file and returns the map with key as timestamps and value as vector of orders */
    static std::map<std::string, std::vector<OrderBookEntry>> readCSV(std::string csvFile);
    
    /** convert the string to a vector of strings using a separator character */
    static std::vector<std::string> tokenise(std::string line, char separator);
    
    /** convert string to order book entry */
    static OrderBookEntry stringToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType orderbookType);
    
    /** convert a obe to a string */
    static std::string tokensToString(OrderBookEntry order);

private:
    /** convert string to order book entry*/
    static OrderBookEntry stringToOBE(std::vector<std::string> strings);
};

#endif /* CSVReader_hpp */
