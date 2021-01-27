//
//  Graph.hpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/19/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include "parallel_hashmap/btree.h"

using namespace std;
using phmap::btree_set;
using ui = unsigned int;

struct Node {
    ui node_id;
    btree_set<ui> neighbors;
};

class Graph {
    ui nodes_count;
    Node* nodes;
    ui edges_count;
public:
    Graph(const char* edge_list_path, ui n_c);
    void printGraph();
    void printInfo();
    void output_orderedEdgeList(const char* output_path = "./ordered_file/ordered_list.dat");
};

#endif /* Graph_hpp */
