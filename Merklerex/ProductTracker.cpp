//
//  ProductTracker.cpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#include "ProductTracker.hpp"

/** Product tracker constructor which takes product name, vector of average prices, slope and a constant */
ProductTracker::ProductTracker(
                               std::string _name,
                               std::vector<double> _price,
                               double _a,
                               double _b) : name(_name), price(_price), a(_a), b(_b) {}
