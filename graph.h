#pragma once
#include <map>
#include "node.h"

using namespace std;
class graph{
  private:
    map<int, node> nodes;
  public:
    map<int, node> getNodeMap();
    void addDependency(int nodeID, int edge);
    void addNode(int nodeID, node nodeIn);
    void setNode(int nodeID, node nodeIn);
    node getNode(int nodeID);
    int size();
};
