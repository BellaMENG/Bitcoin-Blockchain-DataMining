//
//  CSRGraph.hpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/26/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#ifndef CSRGraph_hpp
#define CSRGraph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
using ui = unsigned int;

class CSRGraph {
    // CSR representation
    // we need number of nodes, number of edges
    ui number_nodes;
    ui number_edges;
    // col_index, also out_edges, which is the second col of ordered edge list
    // col_index, has size of number_of_edges
    vector<ui> col_index;
    // row_index, has size of (number_of_nodes + 1)
    // row_index, first element is 0 and last element is number_of_edges
    vector<ui> row_index;
public:
    CSRGraph(const char* ordered_edge_list, bool = true, const char* col_file = "col_index.dat", const char* row_file = "row_index.dat");
    CSRGraph(const char* col_index_file, const char* row_index_file);
    void printInfo();
    void printGraph();
    vector<ui> getNeighbors(ui);
    ui getDegree(ui);
    ui getNumberOfNodes();
    ui getNumberOfEdges();
    ui printNumberOfNodes();
    ui printNumberOfEdges();

// TODO: implement kcores
// TODO: implement bfs/dfs (does it make sense?)
    bool isReachable(ui, ui);
// TODO: implement pagerank

};


#endif /* CSRGraph_hpp */
