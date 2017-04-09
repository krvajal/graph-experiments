//
// Created by Miguel Angel Carvajal on 4/9/17.
//

#ifndef PAKGERANK_SERIAL_NETREADER_H
#define PAKGERANK_SERIAL_NETREADER_H

#include "UnweightedGraph.h"

class NetReader {

  enum LineType { COMMENT_LINE, VERT_LINE, ARC_LINE, ARC_HEADER_LINE, VERT_HEADER_LINE, EDGE_HEADER_LINE, EDGE_LINE };
  enum RegionType { BLANK_REGION, VERT_REGION, ARC_REGION, EDGE_REGION };
public:
  static ulong parseVertHeaderLine(std::string line) {
    std::istringstream inSStream(line);
    std::string header;
    inSStream >> header;
    ulong v;
    inSStream >> v;
    return v;
  }
  static UnweightedGraph readVerts(std::istream &istream, ulong v) {
    UnweightedGraph g(v);

    for (int i = 0; i < v; i++) {
      ulong index;
      std::string label;
      istream >> index;
      getline(istream, label);
      g.setLabel(index, label);
    }
    return g;
  }
  static void parseEdgeLine(std::string line, UnweightedGraph &graph) {
    std::istringstream inSStream(line);
    ulong v;
    inSStream >> v;
    ulong w;
    while (inSStream >> w) {
      graph.addEdge(v, w);
    }

  }
  static ulong getVertexCount(std::istream &istream) {

    RegionType region = RegionType::BLANK_REGION;
    while (!istream.eof()) {
      std::string line = readLine(istream);
      if (getLineType(line, region) == COMMENT_LINE)
        continue;
      if (getLineType(line, region) == VERT_HEADER_LINE) {
        ulong v = parseVertHeaderLine(line);
        return v;
      } else {
        throw int();
      }
    }
    throw int();
  }
  static UnweightedGraph readGraph(std::istream &inStream) {
    RegionType region = RegionType::BLANK_REGION;
    ulong v = getVertexCount(inStream);
    UnweightedGraph g = readVerts(inStream, v);
    while (!inStream.eof()) {
      std::string line = readLine(inStream);
      switch (getLineType(line, region)) {
      case ARC_HEADER_LINE: {
        region = ARC_REGION;
        break;
      }
      case EDGE_HEADER_LINE: {
        region = EDGE_REGION;
        break;
      }
      case EDGE_LINE: {
        parseEdgeLine(line, g);
        break;
      }

      case COMMENT_LINE:break;
      case VERT_LINE:break;
      case ARC_LINE:break;
      default: break;
      }
    }
    return g;
  }
private:
  static LineType getLineType(std::string line, RegionType region) {
    size_t pos = line.find_first_of("%");
    if (pos == 0)
      return COMMENT_LINE;
    pos = line.find("*Vertices");
    if (pos == 0)
      return VERT_HEADER_LINE;
    pos = line.find("*Arcslist");
    if (pos == 0)
      return ARC_HEADER_LINE;
    pos = line.find("*Edgeslist");
    if (pos == 0)
      return EDGE_HEADER_LINE;
    switch (region) {
    case BLANK_REGION:return VERT_LINE;
    case ARC_REGION:return ARC_LINE;
    case EDGE_REGION:return EDGE_LINE;
    case VERT_REGION: return VERT_LINE;
    default: throw int();
    }
  }
  static std::string readLine(std::istream &inStream) {
    std::string line;
    getline(inStream, line);
    return line;

  }

};

#endif //PAKGERANK_SERIAL_NETREADER_H
