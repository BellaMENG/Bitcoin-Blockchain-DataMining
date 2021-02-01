//
//  getExchangeAddressIndex.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/1/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using ui = unsigned int;

void extractIndex(const char*);

int main(int argc, const char* argv[]) {
    
    return 0;
}

void extractIndex(const char* fp) {
    ifstream ifs(fp);
    string tmp_str;
    stringstream ss;
    while(getline(ifs, tmp_str)) {
        ss.clear();
        ss << tmp_str;
        ui addr_id;
        string addr;
        ss >> addr_id >> addr;
    }
}
