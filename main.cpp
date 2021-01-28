//
//  main.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 12/21/20.
//  Copyright © 2020 Bella MENG. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include "parallel_hashmap/phmap.h"
#include "parallel_hashmap/phmap_dump.h"
#include "parallel_hashmap/btree.h"
#include "Graph.hpp"
#include "CSRGraph.hpp"

using namespace std;
using phmap::flat_hash_set;
using phmap::btree_multimap;
using phmap::btree_set;

using ui = unsigned int;

void test_btree_multimap();
void test_graph_class(const char* []);
void test_csrgraph_class(const char* []);
void test_btree_set();
void test_vector();
void test_flat_hash_set();


int main(int argc, const char * argv[]) {
//    test_graph_class(argv);
//    test_btree_set();
//    test_vector();
//    test_flat_hash_set();
//    test_preProcess(argv);
    test_csrgraph_class(argv);
    return 0;
}

void test_csrgraph_class(const char* argv[]) {
    int convert;
    sscanf(argv[2], "%d", &convert);
    cout << "----Testing the CSRGraph class----" << endl;
    cout << "----Build from Edge list----" << endl;
    CSRGraph g1(argv[1], convert, argv[3], argv[4]);
    g1.printInfo();
    g1.printGraph();
    
    cout << endl;
    cout << endl;
    
    cout << "----Build from Binary Files----" << endl;
    CSRGraph g2(argv[3], argv[4]);
    g2.printInfo();
    g2.printGraph();
}


void test_btree_multimap() {
    std::cout << "Hello, World!\n";
    btree_multimap<ui, ui> m;
    
    m.insert(pair<ui, ui>(301, 19));
    m.insert(pair<ui, ui>(301, 20));
    m.insert(pair<ui, ui>(302, 29));
    
    cout << "Number of elements with key 301: " << m.count(301) << endl;
    cout << "Number of elements with key 302: " << m.count(302) << endl;

}

void test_graph_class(const char* argv[]) {
    const char* fp = argv[1];
    ui n;
    sscanf(argv[2], "%u", &n);
    Graph g(fp, n);
    g.printInfo();
//    g.output_orderedEdgeList("test_output.dat");
}

void test_btree_set() {
    auto start = chrono::high_resolution_clock::now();
    btree_set<pair<ui, ui>> test_edges;
    test_edges.insert(make_pair(2, 1));
    test_edges.insert(make_pair(3, 5));
    test_edges.insert(make_pair(1, 3));
    test_edges.insert(make_pair(5, 4));
    test_edges.insert(make_pair(2, 3));
    cout << "test btree_set with pair:" << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Time using btree_set: " << setw(9) << diff.count() << "s\n";
    for (auto itr = test_edges.begin(); itr != test_edges.end(); ++itr) {
        cout << (*itr).first << "\t" << (*itr).second << endl;
    }

}

void test_vector() {
    auto start = chrono::high_resolution_clock::now();
    vector<pair<ui, ui>> test_edges;
    test_edges.push_back(make_pair(2, 1));
    test_edges.push_back(make_pair(3, 5));
    test_edges.push_back(make_pair(1, 3));
    test_edges.push_back(make_pair(5, 4));
    test_edges.push_back(make_pair(2, 3));
    
    sort(test_edges.begin(), test_edges.end(), [](const pair<ui, ui>& left, const pair<ui, ui>& right) {
        if (left.first == right.first) {
            return left.second < right.second;
        }
        return left.first < right.first;
    });
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Time using vector: " << setw(9) << diff.count() << "s\n";
    for (auto itr = test_edges.begin(); itr != test_edges.end(); ++itr) {
        cout << (*itr).first << "\t" << (*itr).second << endl;
    }
}


void test_flat_hash_set() {
    flat_hash_set<pair<ui, ui>> testset;
    cout << "test the return value of the insert function: " << endl;
    cout << (testset.insert(make_pair(1, 2))).second << endl;
    cout << (testset.insert(make_pair(1, 2))).second << endl;
}
