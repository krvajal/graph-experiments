//
// Created by Miguel Angel Carvajal on 4/9/17.
//

#ifndef PAKGERANK_SERIAL_CONNECTEDCOMPONENTS_H
#define PAKGERANK_SERIAL_CONNECTEDCOMPONENTS_H

#include "UnweightedGraph.h"

class ConnectedComponents {

  std::vector<bool> marked_;
  std::vector<int> id_;
  int count_;
public:
  ConnectedComponents(UnweightedGraph g) :
      marked_(g.V() + 1, false), count_(0), id_(g.V()) {
    for (ulong v = 1; v <= g.V(); v++) {
      if (!marked_[v]) {
        dfs(g, v);
        count_++;
        std::cout << count_ << std::endl;
      }
    }
  }
  int count() const { return count_; }
  bool connected(int v, int w) {
    return id_[--v] == id_[--w];
  }

private:
  void dfs(UnweightedGraph g, ulong v) {
    marked_[v] = true;
    id_[v] = count_;

    for (auto w: g.adj(v)) {
      if (!marked_[w]) {
        dfs(g, w);
      }
    }
  }
};

#endif //PAKGERANK_SERIAL_CONNECTEDCOMPONENTS_H
