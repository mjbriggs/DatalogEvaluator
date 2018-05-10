#include "node.h"
void node::addEdge(int edge){
  set<int>::iterator it;
  adjacencyList.insert(edge);
  it = adjacencyList.find(edge);
  //cout << *it << endl;
  //adjacencyVec.push_back(edge);
};
void node::setVisitFlag(){
  visitFlag = !visitFlag;
};
bool node::isVisited(){
  return visitFlag;
};
void node::setPostOrderNum(int PONum){
  postOrderNum = PONum;
};
set<int> node::getEdges(){
  return adjacencyList;
};
vector<int> node::getVec(){
  return adjacencyVec;
};
int node::getPostOrderNum(){
  return postOrderNum;
};
