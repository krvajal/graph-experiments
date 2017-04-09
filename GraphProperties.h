//
// Created by Miguel Angel Carvajal on 4/9/17.
//

#ifndef PAKGERANK_SERIAL_GRAPHPROPERTIES_H
#define PAKGERANK_SERIAL_GRAPHPROPERTIES_H

class GraphProperties {

  UnweightedGraph g_;
  int diameter_;
public:

  GraphProperties(UnweightedGraph g) : g_(g), diameter_(0) {
    for (ulong v = 1; v <= g.V(); v++) {
      int ecc = eccentricity(g, v);
      std::cout << v << ": " << ecc << std::endl;
      if (ecc > diameter_) {
        diameter_ = ecc;
//        std::cout  << diameter_ << std::endl;
      }

    }
  }
  // the maximum eccentricity of any vertex
  int diameter() {
    return diameter_;
  }
private:
  // the length of the shortest path from that vertex
  // to the furthest vertex from v.
  int eccentricity(UnweightedGraph g, ulong s) {
    int ecc = 0;
    std::queue <ulong> qq;
    qq.push(s);
    std::vector<int> depth(g.V(), 0);
    std::vector<bool> marked(g.V(), false);
    depth[s] = 0;
    while (!qq.empty()) {
      ulong v = qq.front();
      qq.pop();
      for (auto w: g.adj(v)) {
        if (!marked[w]) {
          depth[w] = depth[v] + 1;
          marked[w] = true;
          qq.push(w);
          if (depth[w] > ecc)
            ecc = depth[w];
        }
      }
    }
    return ecc;
  }

};

#endif //PAKGERANK_SERIAL_GRAPHPROPERTIES_H
