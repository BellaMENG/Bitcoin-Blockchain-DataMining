//
//  getIndexWithRanks.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/10/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
void get_list_of_indices(const char*, const char*, unsigned long = 1000, bool = false, bool = true);

int main(int argc, const char* argv[]) {
    get_list_of_indices(argv[1], argv[2]);
    return 0;
}

void get_list_of_indices(const char* pr_fp, const char* target_fp, unsigned long number_of_lines, bool with_pr, bool save_as_bin) {
    ifstream ifs(pr_fp, ios::binary);
    
    int data_size;
    unsigned long vsize;
    vector<pair<unsigned int, double>> index_pr;
    ifs.read(reinterpret_cast<char*>(&data_size), 4);
    ifs.read(reinterpret_cast<char*>(&vsize), data_size);
    
    index_pr.resize(vsize);
    ifs.read(reinterpret_cast<char*>(&index_pr.front()), vsize * sizeof(pair<unsigned int, double>));
    
    ofstream ofs(target_fp, ios::binary);
    ofs.write(reinterpret_cast<const char*>(&data_size), 4);
    ofs.write(reinterpret_cast<const char*>(&number_of_lines), data_size);
    
    cout << "With pagerank numbers? " << with_pr << endl;
    
    if (with_pr) {
        ofs.write(reinterpret_cast<const char*>(&index_pr.front()), number_of_lines * sizeof(pair<unsigned int, double>));
    } else {
        vector<unsigned int> index_wo_pr;
        unsigned long id = 0;
        for (auto itr = index_pr.begin(); id++ < number_of_lines; ++itr) {
            index_wo_pr.push_back(itr->first);
        }
        ofs.write(reinterpret_cast<const char*>(&index_wo_pr.front()), number_of_lines * sizeof(unsigned int));
    }
}
