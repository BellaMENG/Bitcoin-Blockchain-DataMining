//
//  PageRank.hpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/5/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#ifndef PageRank_hpp
#define PageRank_hpp

#include <stdio.h>
#include <iostream>
#include "CSRGraph.hpp"

class PageRank {
    
private:
    CSRGraph* graph_;
    CSRGraph* graph_t_;
    
public:
    void initGraph(const char*, const char*, const char*, const char*, const char*, const char*);
    
    CSRGraph* getGraph() const {return graph_;}
    CSRGraph* getGraphT() const {return graph_t_;}
    
    void updateRanks(ui , double , double);
    void printPageRank();
    void outputPageRank(const char*);
};

#endif /* PageRank_hpp */
