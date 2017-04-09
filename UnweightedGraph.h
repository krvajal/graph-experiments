//
// Created by Miguel Angel Carvajal on 4/9/17.
//

#ifndef PAKGERANK_SERIAL_UNWEIGHTEDGRAPH_H
#define PAKGERANK_SERIAL_UNWEIGHTEDGRAPH_H

#include "types.h"

class UnweightedGraph {

  unsigned long V_;
  unsigned long E_;

  std::vector <AdjList> outList_;
  std::vector <AdjList> inList_;
  std::vector <std::string> labels_;
public:
  UnweightedGraph(unsigned long V) :
      V_(V), outList_(V), E_(0), labels_(V), inList_(V) {

  }
  void setLabel(ulong v, const std::string &label) {
    labels_[--v] = label;
  }
  ulong V() const;
  ulong E() const { return E_; }
  void addEdge(ulong v, ulong w) {
    E_++;
    outList_[--v].insert(--w);
    inList_[w].insert(v);
  }
  AdjList adj(ulong v) {
    return outList_[--v];
  }
  AdjList inEdges(int v) {
    return inList_[--v];
  }

  static ulong degree(UnweightedGraph G, int v) {
    return G.adj(v).size();
  }
};
ulong UnweightedGraph::V() const { return V_; }

#endif //PAKGERANK_SERIAL_UNWEIGHTEDGRAPH_H
