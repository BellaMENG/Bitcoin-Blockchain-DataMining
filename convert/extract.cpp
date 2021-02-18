//
//  extract.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 1/8/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include "util.h"

void Usage();
void extractEdgeList(int, const char* []);

int main(int argc, const char * argv[]) {
    extractEdgeList(argc, argv);
    return 0;
}

void Usage() {
    cout << "Usage: [1]type of extract [2]edges file [3]output file";
}

void extractEdgeList(int argc, const char * argv[]) {
    if (argc < 3) {
        Usage();
    } else {
        int extract_type;
        sscanf(argv[1], "%d", &extract_type);
        cout << "extract type: " << extract_type << endl;
        unsigned int txid;
        int addr_in;
        int addr_out;
        double weight;
        
        FILE * EdgeFile;
        EdgeFile = fopen(argv[3], "w");
        
        cout << "----start to output edge list to file: " << endl;
        ifstream inFile(argv[2]);
        while (inFile >> txid >> addr_in >> addr_out >> weight) {
            fprintf(EdgeFile, "%d\t%d\n", addr_in, addr_out);
        }
        fclose(EdgeFile);
    }
}

