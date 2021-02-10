//
//  getAddresses.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/10/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void get_addresses(const char*, const char*, const char*, bool = false);

int main(int argc, const char* argv[]) {
    cout << "why" << endl;
    get_addresses(argv[1], argv[2], argv[3]);
    return 0;
}

void get_addresses(const char* index_fp, const char* addresses_fp, const char* output_fp, bool bin_format) {
    // read in all the index
    cout << "start to get addresses" << endl;
    
    int data_size;
    unsigned long vsize;
    vector<unsigned int> indexv;
    ifstream id_file(index_fp, ios::binary);
    id_file.read(reinterpret_cast<char*>(&data_size), 4);
    id_file.read(reinterpret_cast<char*>(&vsize), data_size);
    id_file.read(reinterpret_cast<char*>(&indexv.front()), vsize * sizeof(unsigned int));
    
    // read in addresses file
    ifstream addr_file(addresses_fp);
    vector<string> addresses;
    
    string tmp_str;
    stringstream ss;
    while(getline(addr_file, tmp_str)) {
        ss.clear();
        ss << tmp_str;
        unsigned int id;
        string addr;
        ss >> id >> addr;
        addresses.push_back(addr);
    }

    // output the selected addresses
    vector<string> selected_addr;
    for (auto itr = indexv.begin(); itr != indexv.end(); ++itr) {
        selected_addr.push_back(addresses[*itr]);
    }
    
    if (bin_format) {
        ofstream ofs(output_fp, ios::binary);
        ofs.write(reinterpret_cast<const char*>(&vsize), sizeof(unsigned long));
        ofs.write(reinterpret_cast<const char*>(&selected_addr.front()), vsize * sizeof(string));
    } else {
        ofstream ofs(output_fp);
        for (auto itr = selected_addr.begin(); itr != selected_addr.end(); ++itr) {
            ofs << *itr << "\n";
        }
    }
}
