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


/** Wallet constructor*/
Wallet::Wallet() {}


/** insert currency to the wallet */
void Wallet::insertCurrency(std::string type, double amount){
    
    
    // if the amount is less than 0, throw exception
    if(amount < 0) throw std::exception{};
    
    // using ternary operator chheck if the currency type is already present or
    // not, if it is present then update the amount by adding the new amount to
    // the old amount, if not present then assign the amount
    currencies[type] = currencies.count(type) == 0 ? amount : currencies[type] + amount;
}


/** check if the wallet contains this much currency or more */
bool Wallet::containsCurrency(std::string type, double amount){
    
    // check if the currency is present in the wallet
    if (currencies.count(type) == 0) return false;
    
    return currencies[type] >= amount;
}


/** remove currency from the wallet */
bool Wallet::removeCurrency(std::string type, double amount) {
    
    // if the amount is less than 0, throw exception
    if(amount < 0) throw std::exception{};
    
    // if the wallet contains the currency with a certain amount then remove it
    if(containsCurrency(type, amount)) {
        currencies[type] -= amount;
        return true;
    } else {
        return false;
    }
}


/** generate a string representation of the wallet */
std::string Wallet::toString() {
    std::string s;
    
    // loop over the curencies and convert them to string to view the string
    // represent of the wallet
    for (std::pair<std::string, double> pair : currencies) {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    
    return s;
}


/** check if the wallet can cope with this ask or bid */
bool Wallet::canFulfillOrder(const OrderBookEntry order) {
    
    // split the product using "/" separator to get the ask or bid currencies
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    
    // check if the order type is ask
    if (order.orderType == OrderBookType::ask) {
        double amount = order.amount;
        std::string currency = currs[0];
        
        std::cout << "[Wallet::canFullfillOrder]: " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    
    // check if the order type is bid
    if(order.orderType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        
        std::cout << "wallet::canFullfillOrder: " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    
    return false;
}


/** updates the content of the wallet  assumes the order was made by the owner of the wallet */
void Wallet::processSale(OrderBookEntry& sale) {
    
    // split the product using "/" separator to get the incoming and outgoing currencies
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    
    
    // check if the sale order type is askSale
    if (sale.orderType == OrderBookType::askSale) {
        // get the outgoing amount
        double outgoingAmount = sale.amount;
        // get the outgoing currency
        std::string outgoingCurrency = currs[0];
        
        // calculate the incoming amount
        double incomingAmount = sale.amount * sale.price;
        // get the incoming currency
        std::string incomingCurrency = currs[1];
        
        // increment and decrement incoming and outgoing amount respectively
        currencies[outgoingCurrency] -= outgoingAmount;
        currencies[incomingCurrency] += incomingAmount;
    
    }
    
    // check if the sale order type is askSale
    if (sale.orderType == OrderBookType::bidSale) {
        // get the incoming amount
        double incomingAmount = sale.amount;
        // get the incoming currency
        std::string incomingCurrency = currs[0];

        // get the outgoing amount
        double outgoingAmount = sale.amount * sale.price;
        // get the outgoing currency
        std::string outgoingCurrency = currs[1];

        // increment and decrement incoming and outgoing amount respectively
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    
   }
    
}
