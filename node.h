#pragma once
#include <set>
#include <vector>
#include <iostream>

using namespace std;
class node{
  private:
    set<int> adjacencyList;
    vector<int> adjacencyVec;
    bool visitFlag = false;
    int postOrderNum;
  public:
    vector<int> getVec();
    set<int> getEdges();
    void addEdge(int edge);
    void setVisitFlag();
    bool isVisited();
    int getPostOrderNum();
    void setPostOrderNum(int PONum);
};
