//
//  generate_example_edgelist.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/21/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;
using ui = unsigned int;

void generateRandomEdgeList(const char* output_fp, ui number_of_edges, ui number_of_nodes) {
    srand((unsigned) time(0));
    ofstream ofs(output_fp);
    cout << "Generating a random edge list with " << number_of_edges << " edges and " << number_of_nodes << " nodes:"<< endl;
    for (ui i = 0; i < number_of_edges; ++i) {
        ui u = rand() % number_of_nodes;
        ui v = rand() % number_of_nodes;
        while (u == v) {
            v = rand() % number_of_nodes;
        }
        ofs << u << "\t" << v << "\t" << "\n";
    }
}

int main(int argc, const char * argv[]) {
    ui num_nodes, num_edges;
    sscanf(argv[2], "%u", &num_edges);
    sscanf(argv[3], "%u", &num_nodes);
    generateRandomEdgeList(argv[1], num_edges, num_nodes);
    return 0;
}
