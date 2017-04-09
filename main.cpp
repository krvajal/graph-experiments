#include <iostream>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

#include "UnweightedGraph.h"
#include "NetReader.h"
#include "GraphProperties.h"
#include "ConnectedComponents.h"
#include "PageRank.h"

int main() {
  std::ifstream inFile("graph.net");
  if (inFile.is_open()) {
    UnweightedGraph g = NetReader::readGraph(inFile);
    std::cout << "V: " << g.V() << std::endl;
    std::cout << "E: " << g.E() << std::endl;

    PageRank pageRank(g);
    ConnectedComponents connectedComponents(g);
    std::cout << connectedComponents.count() << std::endl;
    GraphProperties props(g);
    std::cout << props.diameter() << std::endl;

  } else {
    std::cout << "file not found\n";
  }

}