//
// Created by Miguel Angel Carvajal on 4/9/17.
//

#ifndef PAKGERANK_SERIAL_PAGERANK_H
#define PAKGERANK_SERIAL_PAGERANK_H
#include "UnweightedGraph.h"

class PageRank {

  std::vector<float> pageRank_;
  std::vector<float> pageRankUpdated_;
  float dumpFactor;
  UnweightedGraph g_;
public:
  PageRank(UnweightedGraph g)
      : g_(g), pageRank_(g.V(), 1 / float(g.V())),
        pageRankUpdated_(g.V()) {

    dumpFactor = 0.78;

    for (int iter = 0; iter < 2; iter++) {
      iterate();
//       std::cout << "Iteration count " << iter << std::endl;
    }

  }
  float rank(ulong v) {
    return pageRank_[--v];
  }

private:

  // perform a page rank iteration
  // only a few iterations are needed
  // to achieve convergence
  void iterate() {
    ulong numvert = g_.V();
    for (int vv = 1; vv <= numvert; vv++) {
      AdjList adj = g_.inEdges(vv);
      std::cout << "Processing vertex " << vv << std::endl;
      float rank = 0;
      std::for_each(adj.begin(), adj.end(), [vv, &adj, this, &rank](int w) {
        rank += this->pageRank_[w];
      });
      pageRankUpdated_[vv - 1] = (1 - dumpFactor) / numvert + dumpFactor * rank;
    }
    pageRank_ = pageRankUpdated_;
  }
};

#endif //PAKGERANK_SERIAL_PAGERANK_H
