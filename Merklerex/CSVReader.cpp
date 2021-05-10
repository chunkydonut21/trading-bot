//
//  CSVReader.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 10/05/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "CSVReader.hpp"
#include "OrderBookEntry.hpp"


std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile) {
    std::vector<OrderBookEntry> entries;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string line, char separator) {
    std::vector<std::string> tokens;
    return tokens;
}

OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> strings) {
    OrderBookEntry obe{1, 2, "2021/04/26", "fdfdfdf", OrderBookType::bid};
    return obe;
}
