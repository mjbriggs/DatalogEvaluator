#include "graph.h"
void graph::addNode(int nodeID, node nodeIn){
  nodes.insert(pair<int,node>(nodeID,nodeIn));
};
void graph::setNode(int nodeID, node nodeIn){
   nodes.find(nodeID)->second = nodeIn;
};
void graph::addDependency(int nodeID, int edge){
  nodes.find(nodeID)->second.addEdge(edge);
};
node graph::getNode(int nodeID){
  map<int,node>::iterator it;
  it = nodes.find(nodeID);
  if(it == nodes.end()){
    cout << "Node not found" << endl;
  }
  else{
  //  cout << "node " << nodeID << " found" << endl;
  }
  return nodes.find(nodeID)->second;
};
int graph::size(){
  return nodes.size();
};
map<int, node> graph::getNodeMap(){
  return nodes;
};
