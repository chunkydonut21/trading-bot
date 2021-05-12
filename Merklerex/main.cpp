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

#include <filesystem>

int main() {
    
    MerkelMain app{};
    app.init();
    
//    CSVReader::readCSV("data.csv");
    
    
    return 0;
}
