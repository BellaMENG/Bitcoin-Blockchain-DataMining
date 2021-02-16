//
//  getAddrInfo.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/16/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <blocksci/blocksci.hpp>
#include <iostream>

using namespace std;
using namespace blocksci;

void readAddr(const char*[]);

int main(int argc, const char* argv[]) {
    readAddr(argv);
    return 0;
}

void readAddr(const char* argv[]) {
    Blockchain chain(argv[1]);
}
