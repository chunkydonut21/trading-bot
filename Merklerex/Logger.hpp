//
//  Logger.hpp
//  Merklerex
//
//  Created by Shivam Maheshwari on 19/06/21.
//  Copyright © 2021 Shivam Maheshwari. All rights reserved.
//

#ifndef Log_hpp
#define Log_hpp

#include "OrderBookEntry.hpp"
#include <vector>


#include <stdio.h>


class Logger {
    public:
        /** logger constructor */
        Logger();

        /** export the logbook data to a file */
        void exportToFile();
        /** insert the order in the logbook */
        void logTransaction(OrderBookEntry order, bool marker = false);
        /** insert the wallet balance after each timestamp in the logbook */
        void logWalletBalance(std::string wallet);

    private:
        /** vector of logs which contains information transactions, sales and wallet */
        std::vector<std::string> logBook;
        

};

#endif /* Log_hpp */
