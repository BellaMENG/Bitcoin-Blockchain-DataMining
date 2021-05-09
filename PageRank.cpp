//
//  PageRank.cpp
//  BitcoinBlockchain
//
//  Created by MENG Zihan on 2/5/21.
//  Copyright © 2021 Bella MENG. All rights reserved.
//

#include "PageRank.hpp"
#include <cmath>
#include <fstream>
#include <chrono>

using namespace chrono;
/*
 ./getweights /home/zmengaa/data500k/txedges/datasets/extracted_col.dat /home/zmengaa/data500k/txedges/datasets/extracted_row.dat /home/zmengaa/data500k/txedges/datasets/extracted_deg.dat /home/zmengaa/data500k/txedges/datasets/txedges.dat /home/zmengaa/data500k/txedges/datasets/weights.dat 1
 ----Start to read the col_index to vector----
 data size: 4
 number of edges: 2219053854
 ----Start to read the row_index to vector----
 data size: 4
 number of nodes: 370269747
 Read files time: 9230 ms

 read in or calculate degrees: true
 read in degrees:
 before read file:
 after read file:

 start time elapse:

 size of the weights vector: 1736599145

 number of edges: 2219053854

 Time elapse: 2034017275018 s
 */
void PageRank::initGraph(const char* col_fp, const char* row_fp, const char* degree_fp, const char* col_fp_t, const char* row_fp_t, const char* degree_fp_t) {
    
    graph_ = new CSRGraph();
    graph_t_ = new CSRGraph();
    
    graph_->readFromFile(col_fp, row_fp, degree_fp);
    graph_t_->readFromFile(col_fp_t, row_fp_t, degree_fp_t);

    cout << "finished initialize graphs" << endl;
}

void PageRank::updateRanks(ui iterations, double convergence, double alpha) {
    double sum_pr;
    double dangling_pr;
    double diff = 1;
    vector<double> ranks;
    vector<double> old_pr;
    
    ui num_iterations = 0;
    if (graph_->getNumberOfNodes() == 0)
        return;
    ranks.resize(graph_->getNumberOfNodes());
    ranks[0] = 1;
    
    while (diff > convergence && num_iterations < iterations) {
        sum_pr = 0;
        dangling_pr = 0;
        
        for (ui k = 0; k < ranks.size(); ++k) {
            double cpr = ranks[k];
            sum_pr += cpr;
            if (graph_->getDegree(k) == 0) {
                dangling_pr += cpr;
            }
        }

        if (num_iterations == 0) {
            old_pr = ranks;
        } else {
            for (ui i = 0; i < ranks.size(); ++i) {
                old_pr[i] = ranks[i] / sum_pr;
            }
        }
        
        sum_pr = 1;
        double one_Av = alpha * dangling_pr / graph_->getNumberOfNodes();
        double one_Iv = (1 - alpha) * sum_pr / graph_->getNumberOfNodes();
        
        diff = 0;
        for (ui i = 0; i < graph_->getNumberOfNodes(); ++i) {
            double h = 0.0;
            vector<ui> neighbors = graph_t_->getNeighbors(i);
            for (auto itr = neighbors.begin(); itr != neighbors.end(); ++itr) {
                double h_v = (graph_->getDegree(*itr)) ? (1.0 / graph_->getDegree(*itr)) : 0.0;
                h += h_v * old_pr[*itr];
            }
            h *= alpha;
            ranks[i] = h + one_Av + one_Iv;
            diff += fabs(ranks[i] - old_pr[i]);
        }
        
        num_iterations++;
    }
    graph_->setPr(ranks);
}

void PageRank::printPageRank() {
    graph_->printPageRank();
}

void PageRank::outputPageRank(const char* pr_fp) {
    int data_size = sizeof(double);
    vector<double> pr = graph_->getPr();
    unsigned long pr_size = pr.size();
    
    ofstream ofs(pr_fp, ios::binary);
    ofs.write(reinterpret_cast<const char*>(&data_size), 4);
    ofs.write(reinterpret_cast<const char*>(&pr_size), sizeof(unsigned long));
    ofs.write(reinterpret_cast<const char *>(&pr.front()), pr.size() * data_size);
    cout << "finished writing pageranks to file, the size of the vector is: " << pr.size() << endl;
}
