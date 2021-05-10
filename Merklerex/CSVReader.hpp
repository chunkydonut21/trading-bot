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

class CSVReader {
public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

private:
    static std::vector<std::string> tokenise(std::string line, char separator);
    static OrderBookEntry stringToOBE(std::vector<std::string> strings);
};

#endif /* CSVReader_hpp */




//user will give the csv file =>
//read single line => tokenise => [dsd,dsd,dsd,dsdd] =>
//convert that vector of strings to the OrderBookEntry object =>
//return the vector of OrderBookEntry object by looping over the csv file
//=> so input is csv file and return type is vector of OrderBookEntry



