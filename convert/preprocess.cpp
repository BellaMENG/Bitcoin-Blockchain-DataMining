//
//  preprocess.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/27/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

#include "../parallel_hashmap/phmap.h"

using namespace std;
using phmap::flat_hash_set;
using ui = unsigned int;

void test_preProcess(const char* []);
void pre_process_edge_list(const char*, const char*, ui &, ui &, ui &, bool = true);

void test_convert(const char* []);
void convertToCSR(const char*, const char*, const char*);


int main(int argc, const char* argv[]) {
    test_convert(argv);
    return 0;
}

void test_preProcess(const char* argv[]) {
    ui n;
    int directed;
    sscanf(argv[2], "%u", &n);
    sscanf(argv[3], "%d", &directed);
    ui min_ele, max_ele, number_edges;
    min_ele = UINT_MAX;
    max_ele = 0;
    pre_process_edge_list(argv[1], argv[2], min_ele, max_ele, number_edges, directed);
}

void pre_process_edge_list(const char* edge_list_fp, const char* target_file_name, ui &min_ele, ui &max_ele, ui &number_edges, bool directed) {
    
    auto start = chrono::high_resolution_clock::now();
    max_ele = 0;
    min_ele = UINT_MAX;
    
    flat_hash_set<pair<ui, ui>> edges_set;
    vector<pair<ui, ui>> edges_list;
    ifstream edge_list(edge_list_fp);
    ui u, v;
    ui original_size = 0;
    string tmp_str;
    stringstream ss;
        
    while (getline(edge_list, tmp_str)) {
        original_size++;
        
        ss.clear();
        ss << tmp_str;
        long tmp1, tmp2;
        ss >> tmp1 >> tmp2;
        if (tmp1 == -1 || tmp2 == -1) {
            continue;
        }
        else {
            u = tmp1;
            v = tmp2;
        }
        if (u == v) {
            continue;
        }
        if (!directed) {
            if (u > v) {
                ui tmp = u;
                u = v;
                v = tmp;
            }
        }
        if ((edges_set.insert(make_pair(u, v))).second) {
            edges_list.push_back(make_pair(u, v));
            if (u > v) {
                if (u > max_ele)
                    max_ele = u;
                if (v < min_ele)
                    min_ele = v;
            } else {
                if (v > max_ele)
                    max_ele = v;
                if (u < min_ele)
                    min_ele = u;
            }
        }
    }
    number_edges = edges_set.size();
    cout << "original edge count is: " << original_size << endl;
    cout << "min_ele is: " << min_ele << ", max_ele is: " << max_ele << ", and number of edges is: " << number_edges << ".\n";

    auto mid = chrono::high_resolution_clock::now();
    chrono::duration<double> diff1 = mid - start;
    cout << "Time of preprocessing: " << setw(9) << diff1.count() << "s\n";
    
    cout << "----start to sort the vector----" << endl;
    sort(edges_list.begin(), edges_list.end(), [](const pair<ui, ui>& left, const pair<ui, ui>& right) {
        if (left.first == right.first) {
            return left.second < right.second;
        }
        return left.first < right.first;
    });

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff2 = end - mid;
    cout << "Time of sorting vector: " << setw(9) << diff2.count() << "s\n";
    
    // Display the graph if the size is not too large
    if (number_edges <= 50) {
        cout << "the graph is: \n";
        for (auto itr = edges_list.begin(); itr != edges_list.end(); ++itr) {
            cout << (*itr).first << "\t" << (*itr).second << endl;
        }
    }
    
    // output the ordered edge list
    cout << "----start to output the sorted edge list----" << endl;
    string underscore = "_";
    string file_extension = ".dat";
    ofstream processed_list(target_file_name + underscore + to_string(min_ele) + underscore + to_string(max_ele) + underscore + to_string(number_edges) + underscore + to_string(original_size) + file_extension);

    for (auto itr = edges_list.begin(); itr != edges_list.end(); ++itr) {
        processed_list << (*itr).first << "\t" << (*itr).second << "\n";
    }
}

void test_convert(const char* argv[]) {
    convertToCSR(argv[1], argv[2], argv[3]);
}

void convertToCSR(const char* edgeList, const char* target_col_file, const char* target_row_file) {
    // edgeList should contain ordered edge list of the graph
    // TODO: Add a step to check whether ordered and call the preprocess function
    auto start = chrono::high_resolution_clock::now();
    ifstream ifs(edgeList);
    
    ui number_edges = 0;
    ui number_nodes = 0;
    vector<ui> col_index;
    vector<ui> row_index;
    
    ui prev_u = -1;
    ui curr_u = 0;

    string tmp_str;
    stringstream ss;
    while(getline(ifs, tmp_str)) {
        ss.clear();
        ss << tmp_str;
        ui u, v;
        ss >> u >> v;
        col_index.push_back(v);
        curr_u = u;
        if (prev_u != curr_u) {
            row_index.push_back(number_edges);
        }
        prev_u = curr_u;
        number_edges++;
        if (ifs.eof())
            break;
    }
    row_index.push_back(number_edges);
    
    number_nodes = curr_u + 1;

    ofstream cols(target_col_file, ios::binary);
    cout << "----Start to output the col_index to file----" << endl;
    int data_size = sizeof(unsigned int);
    cols.write(reinterpret_cast<const char*>(&data_size), 4);
    cols.write(reinterpret_cast<const char*>(&number_edges), data_size);
    cols.write(reinterpret_cast<const char *>(&col_index.front()), col_index.size() * data_size);
    
    ofstream rows(target_row_file, ios::binary);
    cout << "----Start to output the row_index to file----" << endl;
    rows.write(reinterpret_cast<const char*>(&data_size), 4);
    rows.write(reinterpret_cast<const char*>(&number_nodes), data_size);
    rows.write(reinterpret_cast<const char *>(&row_index.front()), row_index.size() * data_size);
    auto end = chrono::high_resolution_clock::now();
    cout << "Output to files time: " << chrono::duration<double>(end - start).count() << " s\n";
    cout << endl;
}
