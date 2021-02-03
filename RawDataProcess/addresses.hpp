//
//  addresses.hpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/1/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#ifndef addresses_hpp
#define addresses_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using ui = unsigned int;

class bitcoinAddress {
    ui id;
    ui balance;
    string address;
};

#endif /* addresses_hpp */
