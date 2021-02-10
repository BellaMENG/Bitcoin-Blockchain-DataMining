//
//  sortPageRank.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/9/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void sortPR(const char*, const char*, unsigned long = 370269747, bool = false);

int main(int argc, const char* argv[]) {
    sortPR(argv[1], argv[2]);
    return 0;
}


void sortPR(const char* pr_fp, const char* sortedpr_fp, unsigned long pr_size, bool read_size) {
    vector<double> orig_pr;
    
    ifstream pr_file(pr_fp, ios::binary);
    int data_size = sizeof(double);
    if (read_size) {
        pr_file.read(reinterpret_cast<char *>(&data_size), 4);
        pr_file.read(reinterpret_cast<char *>(&pr_size), sizeof(unsigned long));
    }
    orig_pr.resize(pr_size);
    pr_file.read(reinterpret_cast<char *>(&orig_pr.front()), sizeof(data_size)*pr_size);
    
    // start to sort the ranks according to their pagerank
    vector<pair<unsigned int, double>> index_pr;
    index_pr.resize(pr_size);
    
    unsigned int index = 0;
    for (auto itr = orig_pr.begin(); itr != orig_pr.end(); ++itr) {
        index_pr.push_back(make_pair(index++, *itr));
    }
    
    auto start = high_resolution_clock::now();
    // sort in descending order
    sort(index_pr.begin(), index_pr.end(), [](const pair<unsigned int, double> &left, const pair<unsigned int, double> &right) {
        return left.second > right.second;
    });
    auto end = high_resolution_clock::now();
    cout << "Sorting time elapsed: " << duration<double>(end-start).count() << "s\n";
    
    // output the result to files first
    data_size = sizeof(unsigned long);
    unsigned long vsize = index_pr.size();
    
    ofstream ofs(sortedpr_fp, ios::binary);
    ofs.write(reinterpret_cast<const char*>(&data_size), 4);
    ofs.write(reinterpret_cast<const char*>(&vsize), data_size);
    ofs.write(reinterpret_cast<const char*>(&index_pr.front()), vsize * sizeof(pair<unsigned int, double>));
}
