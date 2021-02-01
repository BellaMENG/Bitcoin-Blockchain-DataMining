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
#include <chrono>
#include <list>

using namespace chrono;

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
        int data_size = sizeof(unsigned int);
        cols.write(reinterpret_cast<const char*>(&data_size), 4);
        cols.write(reinterpret_cast<const char*>(&number_edges), data_size);
        cols.write(reinterpret_cast<const char *>(&col_index.front()), col_index.size() * data_size);
        
        ofstream rows(target_row_file, ios::binary);
        cout << "----Start to output the row_index to file----" << endl;
        rows.write(reinterpret_cast<const char*>(&data_size), 4);
        rows.write(reinterpret_cast<const char*>(&number_nodes), data_size);
        rows.write(reinterpret_cast<const char *>(&row_index.front()), row_index.size() * data_size);
    }
    cout << "Finish building the graph" << endl;
    cout << endl;
}

CSRGraph::CSRGraph(const char* col_index_file, const char* row_index_file) {
    // TODO: directly import col_index and row_index to two vectors
    auto start = high_resolution_clock::now();
    
    ifstream col_file(col_index_file, ios::binary);
    cout << "----Start to read the col_index to vector----" << endl;
    int data_size;
    col_file.read(reinterpret_cast<char *>(&data_size), 4);
    cout << "data size: " << data_size << endl;
    
    col_file.read(reinterpret_cast<char *>(&number_edges), data_size);
    cout << "number of edges: " << number_edges << endl;
    col_index.resize(number_edges);
    col_file.read(reinterpret_cast<char *>(&col_index.front()), sizeof(data_size)*number_edges);

    
    ifstream row_file(row_index_file, ios::binary);
    cout << "----Start to read the row_index to vector----" << endl;

    row_file.read(reinterpret_cast<char *>(&data_size), 4);
    cout << "data size: " << data_size << endl;
    
    row_file.read(reinterpret_cast<char *>(&number_nodes), data_size);
    cout << "number of nodes: " << number_nodes << endl;
    
    row_index.resize(number_nodes+1);
    row_file.read(reinterpret_cast<char *>(&row_index.front()), sizeof(data_size)*(number_nodes+1));

    auto end = high_resolution_clock::now();
    
    cout << "Read files time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    cout << endl;
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

vector<ui> CSRGraph::getNeighbors(ui node_id) {
    vector<ui> neighbors;
    if (node_id < 0 || node_id >= number_nodes) {
        cerr << "invalid node id" << endl;
        return neighbors;
    }
    ui row_start = row_index[node_id];
    ui row_end = row_index[node_id+1];
    for (ui i = row_start; i < row_end; ++i) {
        neighbors.push_back(col_index[i]);
    }
    return neighbors;
}

ui CSRGraph::getDegree(ui node_id) {
    if (node_id < 0 || node_id >= number_nodes) {
        cerr << "invalid node id" << endl;
        return -1;
    }
    ui row_start = row_index[node_id];
    ui row_end = row_index[node_id+1];
    return (row_end - row_start);
}

ui CSRGraph::getNumberOfNodes() {
    return number_nodes;
}

ui CSRGraph::getNumberOfEdges() {
    return number_edges;
}

ui CSRGraph::printNumberOfNodes() {
    cout << "Number of nodes in this graph: " << number_nodes << endl;
    return number_nodes;
}

ui CSRGraph::printNumberOfEdges() {
    cout << "Number of edges in this graph: " << number_edges << endl;
    return number_edges;
}

bool CSRGraph::isReachable(ui s, ui d) {
    if (s == d)
        return true;
    
    bool *visited = new bool[number_nodes];
    for (ui i = 0; i < number_nodes; ++i) {
        visited[i] = false;
    }
    
    // Initialize BFS algo
    visited[s] = true;
    list<ui> bfs;
    bfs.push_back(s);
    
    while (!bfs.empty()) {
        s = bfs.front();
        bfs.pop_front();
        // iterate through adj list of node s
        vector<ui> neighbors = this->getNeighbors(s);
        for (auto itr = neighbors.begin(); itr != neighbors.end(); ++itr) {
            if (*itr == d)
                return true;
            if (!visited[*itr]) {
                visited[*itr] = true;
                bfs.push_back(*itr);
            }
        }
    }
    return false;
}
