//
//  Wallet.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 03/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "Wallet.hpp"
#include "CSVReader.hpp"
#include <iostream>


Wallet::Wallet() {}

void Wallet::insertCurrency(std::string type, double amount){
    
    if(amount < 0) throw std::exception{};
    
    currencies[type] = currencies.count(type) == 0 ? amount : currencies[type] + amount;
}

bool Wallet::containsCurrency(std::string type, double amount){
    if (currencies.count(type) == 0) return false;
    return currencies[type] >= amount;
}


bool Wallet::removeCurrency(std::string type, double amount) {
    if(amount < 0) throw std::exception{};
    
    if(containsCurrency(type, amount)) {
        currencies[type] -= amount;
        return true;
    } else {
        return false;
    }
}

std::string Wallet::toString() {
    std::string s;
    for (std::pair<std::string, double> pair : currencies) {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    
    return s;
}



bool Wallet::canFulfillOrder(const OrderBookEntry order) {
    
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    
    // ETH/BTC,5,20
    // I want to sell 20 ether for 5 bitcoin
    
    if (order.orderType == OrderBookType::ask) {
        double amount = order.amount;
        std::string currency = currs[0];
        
        std::cout << "wallet::canFullfillOrder: " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    
    // bid
    
    // ETH/BTC,5,50
    // I want to buy 5 Ether and I am willing to sell 50 BTC for 1 ETH, which means I need 5 * 50 = 250 bitcoin in my wallet.
    
    if(order.orderType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        
        std::cout << "wallet::canFullfillOrder: " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    
    return false;
}


void Wallet::processSale(OrderBookEntry& sale) {
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    
    
    // ask
    
    if (sale.orderType == OrderBookType::askSale) {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];
        
        currencies[outgoingCurrency] -= outgoingAmount;
        currencies[incomingCurrency] += incomingAmount;
    }
    
    // bid
    
   if (sale.orderType == OrderBookType::bidSale) {
       double incomingAmount = sale.amount;
       std::string incomingCurrency = currs[0];
       
       double outgoingAmount = sale.amount * sale.price;
       std::string outgoingCurrency = currs[1];
       
       currencies[incomingCurrency] += incomingAmount;
       currencies[outgoingCurrency] -= outgoingAmount;
   }
    
}
