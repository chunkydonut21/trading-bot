//
//  Wallet.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 03/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef Wallet_hpp
#define Wallet_hpp

#import "OrderBookEntry.hpp"
#include <stdio.h>
#include <string>
#include <map>

class Wallet {
public:
    Wallet();
    
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** check if the wallet contains this much currency or more */
    bool containsCurrency(std::string type, double amount);
    /** check if the wallet can cope with this ask or bid */
    bool canFulfillOrder(OrderBookEntry order);
    
    /** updates the content of the wallet  assumes the order was made by the owner of the wallet */
    void processSale(OrderBookEntry& sale);
    /** generate a string representation of the wallet */
    std::string toString();
    
private:
    /** map of key and values with key as name and value as price */
    std::map<std::string, double> currencies;
};

#endif /* Wallet_hpp */
