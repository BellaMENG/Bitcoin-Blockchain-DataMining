//
//  Graph.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/19/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <fstream>
#include <iostream>
#include "Graph.hpp"

using phmap::btree_set;

Graph::Graph(const char* edge_list_path, ui n_c) {
    nodes_count = n_c;
    nodes = new Node[n_c];
    ifstream edge_list(edge_list_path);
    ui u, v;
    ui edges = 0;
    while (edge_list >> u >> v) {
        edges++;
        nodes[u].neighbors.insert(v);
    }
    edges_count = edges;
}

void Graph::printGraph() {
    if (edges_count > 100) {
        cout << "This isn't a demo graph. It has more than 100 edges, so it is not feasible to print the graph" << endl;
        return;
    }
    cout << "number of nodes in the graph: " << nodes_count << endl;
    cout << "adjacency list:" << endl;
    for (int i = 0; i < nodes_count; ++i) {
        cout << "node id: " << i << ", neighbors: ";
        for (auto itr = nodes[i].neighbors.begin(); itr != nodes[i].neighbors.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
}

void Graph::printInfo() {
    cout << "number of nodes in this graph: " << nodes_count << endl;
    cout << "number of edges in this graph: " << edges_count << endl;
}

void Graph::output_orderedEdgeList(const char* output_path) {
    // TODO: This doesn't work when nodes_count is large.
    cout << "outputing ordered edge list: " << endl;
    ofstream orderedList_ofs(output_path);
    
    for (ui i = 0; i < nodes_count; ++i) {
        for (auto itr = nodes[i].neighbors.begin(); itr != nodes[i].neighbors.end(); ++itr) {
            // TODO: finish the output of a file
            orderedList_ofs << i << "\t" << *itr << "\n";
        }
    }
    
}
