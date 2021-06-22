//
//  Currency.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 20/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef Currency_hpp
#define Currency_hpp

#include <stdio.h>
#include <string>

class Currency {
public:
    Currency(std::string name, double amount, double amountOnHold);
    
    std::string name;
    double amount;
    double amountOnHold;
};

#endif /* Currency_hpp */
