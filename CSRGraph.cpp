//
//  CSRGraph.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/26/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include "CSRGraph.hpp"
#include <fstream>
#include <sstream>
#include <string>

CSRGraph::CSRGraph(const char* ordered_edge_list, bool convertEdgeList, const char* target_col_file, const char* target_row_file) {
    ifstream ifs(ordered_edge_list);
    
    number_edges = 0;
    
    ui prev_u = -1;
    ui curr_u = 0;

    string tmp_str;
    stringstream ss;
    while(getline(ifs, tmp_str)) {
        
        ss.clear();
        ss << tmp_str;
        ui u, v;
        ss >> u >> v;
        cout << u << " " << v << endl;
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
    if (convertEdgeList) {
        // TODO: append number_nodes to row_index, and number_edges to col_index
        ofstream cols(target_col_file, ios::binary);
        cout << "----Start to output the col_index to file----" << endl;
        cols.write(reinterpret_cast<const char *>(&col_index.front()), col_index.size() * 4);
        
        ofstream rows(target_row_file, ios::binary);
        cout << "----Start to output the row_index to file----" << endl;
        rows.write(reinterpret_cast<const char *>(&row_index.front()), row_index.size() * 4);
    }
}

CSRGraph::CSRGraph(const char* col_index_file, const char* row_index_file) {
    // TODO: directly import col_index and row_index to two vectors
}

void CSRGraph::printInfo() {
    cout << "The following are the information about this graph: \n";
    cout << "The number of nodes in this graph is: " << number_nodes;
    cout << ", and the number of edges in this graph is: " << number_edges;
    cout << endl;
}

void CSRGraph::printGraph() {
    if (number_edges >= 50 || number_nodes >= 50) {
        cout << "The size of this graph is too large to print. Terminated." << endl;
        return ;
    }
    cout << "------content of col_index vector------" << endl;
    for (auto itr = col_index.begin(); itr != col_index.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;
    cout << "------content of row_index vector------" << endl;
    for (auto itr = row_index.begin(); itr != row_index.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;
}
