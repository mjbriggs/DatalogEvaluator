#pragma once
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <algorithm>
#include <sstream>
#include "schema.h"
#include "tuple.h"
#include "relation.h"
#include "datalogProgram.h"
#include "node.h"
#include "graph.h"

using namespace std;
class database {
  private:
    map<string, relation> relations;
    graph dependencyGraph;
    graph reverseGraph;
    stack<int> nodeOrder;
    int postOrderNum = 1;
    set<int> SCCTree;
    vector<set<int>> stronglyConnectedComponents;
  public:
    void unMarkNodes();
    void dfsForest();
    void dfs(int nodeID);
    void SCCdfs(int nodeID);
    void findSCC();
    void interpreter(datalogProgram datalog);
    void printRules(set<int> &tempSet, int &componentLength);
    void makeGraphs(vector<rule> &rules);
    void printDependencyGraph();
    void ruleEvaluation(set<int> &tempSet, vector<relation> &rightHandRelations, vector<predicate> &rightHandPredicates, vector<rule> &rules);
    void evaluateSchemes();
    void evaluateFacts(vector<predicate> facts);
    void evaluateQueries(vector<predicate> queries); //too complex
    void evaluateRules(vector<rule> rules); //too complex
    void populateDatabase(vector<predicate> &rightHandPredicates, relation &tempRelation, vector<relation> &rightHandRelations);
};
