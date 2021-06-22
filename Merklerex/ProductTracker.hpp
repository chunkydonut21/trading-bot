//
//  ProductTracker.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef ProductTracker_hpp
#define ProductTracker_hpp

#include <stdio.h>
#include <vector>
#include <string>

class ProductTracker {
public:
    
    /** Product tracker constructo which takes product name, vector of average prices, slope and a constant */
    ProductTracker(std::string name, std::vector<double> price, double a, double b);
    
    /** product name */
    std::string name;
    /** vector of average prices */
    std::vector<double> price;
    /** slope */
    double a;
    /** constant */
    double b;
    
};

#endif /* ProductTracker_hpp */
