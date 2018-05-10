#include "database.h"

void database::interpreter(datalogProgram datalog){
  vector<predicate> schemes = datalog.returnSchemes();
  //relation relationIn;
  for(auto&& scheme: schemes){
    //int length = scheme.parametersLength();
    relation relationTemp; //think about making private var that gets cleared
    //cout << scheme.toString() << endl;
    relationTemp.setSchemes(scheme.getParameterString());
    relationTemp.setName(scheme.returnHeadStr());
    relations.insert(pair<string, relation>(scheme.returnHeadStr(), relationTemp));
  }
  map<std::string, relation>::iterator it = relations.begin();
	// Iterate over the map using Iterator till end.
	while (it != relations.end())
	{
		// Accessing KEY from element pointed by it.
		string word = it->first;

		// Accessing VALUE from element pointed by it.
		//int count = it->second;
    //cout << word << endl;
    //it->second.printSchema();
		// Increment the Iterator to point to next entry
		it++;
	}
  evaluateFacts(datalog.returnFacts());
  evaluateRules(datalog.returnRules());
  evaluateQueries(datalog.returnQueries());
};
void database::evaluateSchemes(){};
void database::evaluateFacts(vector<predicate> facts){
  string factID = "";
  for(auto&& fact: facts){
    //int length = scheme.parametersLength();
  //  relation relationTemp; //think about making private var that gets cleared
    //cout << scheme.toString() << endl;
    factID = fact.returnHeadStr();
    relations.find(factID)->second.setTuple(fact.getParameterString());
    //relations.find(factID)->second.printRows();
    /*vector <string> parameter = fact.getParameterString();
    int len = parameter.size();
    for(int i = 0; i < len; i++){
      cout << parameter.at(i) << endl;
    }*/
    //relations.find(factID)->second.printRows();
    //cout << factID << endl;
    //relations.find(factID)->second.printRows();
    factID = "";
    //relationTemp.setSchemes(scheme.getParameterString());
    //relations.insert(pair<string, relation>(scheme.returnHeadStr(), relationTemp));
  }
  //cout << relations.find('a') << endl;
};
void checkFirstParam(string &parameter, relation &tempRelation, int &position, set<int> &columnsToProject, vector<string> &variables){
  if(parameter[0] == '\''){
    tempRelation.select(position, parameter);
    position++;
  }
  else{
    variables.push_back(parameter);
    columnsToProject.insert(position);
    position++;
  }
}
void database::populateDatabase(vector<predicate> &rightHandPredicates, relation &tempRelation, vector<relation> &rightHandRelations){
  int position = 0;
  int len = 0;
  set<int> columnsToProject;
  vector<string> variables;
  vector<string> parameters;
  string parameter = "";
  string predicateID = "";
  string s1 = "";
  bool matched;
  for(auto&& predicate : rightHandPredicates){//now we iterate through each predicate to populate our database
    position = 0;
    columnsToProject.clear();
    variables.clear();
    predicateID = predicate.returnHeadStr();
    len = predicate.parametersLength();
    parameters = predicate.getParameterString();
    parameter = parameters.at(0);
    tempRelation = relations.find(predicateID)->second;
    checkFirstParam(parameter, tempRelation, position, columnsToProject, variables);
    while(position < len){
      parameter = parameters.at(position);
      matched = false;
      if(parameter[0] == '\''){
        tempRelation.select(position, parameter);
        //outRelation.printRows();
      }
      else{
        for(int i = 0; i < position; i++){
          s1 = parameters.at(i);
          if(s1 == parameter){
            tempRelation.select(i, position);
            //outRelation.printRows();
            matched = true;
          }
        }
        if(!matched){
          variables.push_back(parameter);
          columnsToProject.insert(position);
        }
      }
      position++;
    }
    tempRelation.project(columnsToProject);
    tempRelation.rename(variables);//I dont think we need to check if the scheme is empty
    rightHandRelations.push_back(tempRelation);
  }
};
void database::unMarkNodes(){
  map<int, node>::iterator it;
  map<int, node> revNodes = reverseGraph.getNodeMap();
  for(it = revNodes.begin(); it != revNodes.end(); ++it){
    it->second.setVisitFlag();
  }
  //revNodes = reverseGraph.getNodeMap();
}
void database::findSCC(){
  int tempNodeID = 0;
  //cout << "In findSCC" << endl;
  //unMarkNodes();
  while(!nodeOrder.empty()){
    SCCTree.clear();
    tempNodeID = nodeOrder.top();
    //cout << "R" << tempNodeID << endl;
    nodeOrder.pop();
    //dfs(tempNodeID);
    SCCdfs(tempNodeID);
    if(!SCCTree.empty()){
      //set<int>::iterator it;
      /*cout << "Components begin" << endl;
      for(it = SCCTree.begin(); it != SCCTree.end(); ++it){
        cout << "R" << *it << endl;
      }
      cout << "Components end" << endl;*/
      stronglyConnectedComponents.push_back(SCCTree);
    }
  }
//  cout << "There are "<< stronglyConnectedComponents.size() << " SCC's" << endl;

};
void database::SCCdfs(int nodeID){
//  cout << "calling dfs on node " << nodeID << endl;
  node currentNode = dependencyGraph.getNode(nodeID);
  set<int> children = dependencyGraph.getNode(nodeID).getEdges();
  set<int>::iterator it;
  if(!currentNode.isVisited()){
    //cout << "marking visit flag of node " << nodeID << endl;
    currentNode.setVisitFlag();
    dependencyGraph.setNode(nodeID, currentNode);
    for(it = children.begin(); it != children.end(); ++it){
      SCCdfs(*it);
    }
    //cout << "Inserting node "<< nodeID << endl;
    SCCTree.insert(nodeID);
    //nodeOrder.push(nodeID);
    //currentNode.setPostOrderNum(postOrderNum);
    //dependencyGraph.setNode(nodeID, currentNode);
    //cout <<"R" << nodeID << " : " << postOrderNum << endl;
    //postOrderNum++;
  }
};
void database::dfsForest(){
//  cout << "calling dfsForest" << endl;
  map<int, node>::iterator it;
  map<int, node> revNodes = reverseGraph.getNodeMap();
  for(it = revNodes.begin(); it != revNodes.end(); ++it){
    dfs(it->first);//calls dfs on node ID for each node
  }
  revNodes = reverseGraph.getNodeMap();
  /*cout << "Post order list" << endl;
  for(it = revNodes.begin(); it != revNodes.end(); ++it){
    cout << "R" << it->first << " : " << it->second.getPostOrderNum() << endl;
    //dfs(it->first);//calls dfs on node ID for each node
  }*/
  //dfs(0); //calls dfs on first node of reverseGraph
};
void database::printRules(set<int> &tempSet, int &componentLength){
  set<int>::iterator it = tempSet.begin();
  int iterCount = 0;
  while(it != tempSet.end()){
    if(iterCount <  componentLength - 1)
      cout << "R" << *it << ",";
    else
      cout << "R" << *it;
    iterCount++;
    ++it;
  }
  cout << endl;
};
void database::dfs(int nodeID){
  //cout << "calling dfs on node " << nodeID << endl;
  node currentNode = reverseGraph.getNode(nodeID);
  set<int> children = reverseGraph.getNode(nodeID).getEdges();
  set<int>::iterator it;
  if(!currentNode.isVisited()){
    //cout << "marking visit flag of node " << nodeID << endl;
    currentNode.setVisitFlag();
    reverseGraph.setNode(nodeID, currentNode);
    for(it = children.begin(); it != children.end(); ++it){
      dfs(*it);
    }
    //cout << "Inserting node "<< nodeID << endl;
    SCCTree.insert(nodeID);
    nodeOrder.push(nodeID);
    currentNode.setPostOrderNum(postOrderNum);
    reverseGraph.setNode(nodeID, currentNode);
    //cout <<"R" << nodeID << " : " << postOrderNum << endl;
    postOrderNum++;
  }
  return;
};
void database::makeGraphs(vector<rule> &rules){
  cout << "Dependency Graph" << endl;
  node emptyNode;
  int predicateLength = 0;
  vector<predicate> rightHandPredicates;
  set<int> nodeEdges;
  int ruleLength = rules.size();
  predicate headPredicate;
  set<int>::iterator it;
  for(int i = 0; i < ruleLength; i++){
    dependencyGraph.addNode(i, emptyNode);
    reverseGraph.addNode(i, emptyNode);
  }
  for(int i = 0; i < ruleLength; i++){
    //dependencyGraph.addNode(i, tempNode);
    //node tempNode;
    //node revNode;
  //  cout << rules.at(i).toString() << endl;
    rightHandPredicates = rules.at(i).returnPredicates();
    predicateLength = rightHandPredicates.size();
    for(int j = 0; j < predicateLength; j++){
      for(int k = 0; k < ruleLength; k++){
        headPredicate = rules.at(k).returnheadPredicate();
        //cout << rightHandPredicates.at(j).returnHeadStr() << endl;
      //  cout << headPredicate.returnHeadStr() << endl;
        if(rightHandPredicates.at(j).returnHeadStr() == headPredicate.returnHeadStr()){
          //cout << "adding edge R" << k << " for R" << i << endl;
          //tempNode.addEdge(k);
          //revNode.addEdge(i);
          dependencyGraph.addDependency(i, k);
          reverseGraph.addDependency(k, i);
          //nodeEdges.insert(k);
        }
      }
    }
    //dependencyGraph.setNode(i, tempNode);
    //reverseGraph.addNode(i, revNode);
  }
  //int edgeCount = 0;
  //int edgeLength = 0;
  //printDependencyGraph();
  //dependencySize = reverseGraph.size();
};
void database::printDependencyGraph(){
  int nodeCount = 0;
  int nodeLength = 0;
  set<int> nodeEdges;
  set<int>::iterator it;
  int dependencySize = dependencyGraph.size();
  for(int j = 0; j < dependencySize; j++){
    nodeEdges = dependencyGraph.getNode(j).getEdges();
    nodeLength = nodeEdges.size();
    cout << "R" << j << ":";
    if(!nodeEdges.empty()){
      //cout << "empty set" << endl;
      nodeCount = 0;
      for(it = nodeEdges.begin(); it != nodeEdges.end(); ++it){
        if(nodeCount < nodeLength - 1){
          cout << "R" << *it << ",";
        }
        else{
          cout << "R" << *it;
        }
        nodeCount++;
      }
    }
      cout << endl;
  }
};
void joinRelations(int &rightLen, vector<relation> &rightHandRelations){
  while(rightLen > 1){ //joins until there is one tuple
    //cout << "Joining" << endl;
    rightHandRelations.at(0).join(rightHandRelations.at(1)); //combines the 1st and 2nd tuple
    rightHandRelations.erase(rightHandRelations.begin() + 1); //removes the 2nd tuple
    rightLen = rightHandRelations.size(); //updates length
  }
};
void database::ruleEvaluation(set<int> &tempSet, vector<relation> &rightHandRelations, vector<predicate> &rightHandPredicates, vector<rule> &rules){
  set<int>::iterator it = tempSet.begin();
  int componentLength = tempSet.size();
  node tempNode = dependencyGraph.getNode(*it);
  set<int>::iterator edgeIt;
  set<int> edges = tempNode.getEdges();
  relation tempRelation;
  string headId = "";
  string output = "";
  bool tupleAdded;
  relation headRelation;
  int rightLen = 0;
  int count = 0;
  int oldSize = 0;
  int currentSize = 0;
  set <Tuple> newTuples;

  if(componentLength <= 1 && edges.find(*it) == edges.end()){
    cout << "SCC: R" << *it << endl;
    cout << rules.at(*it).toString() << endl;
      //rule = rules.at(ruleIndex);
      headId = rules.at(*it).returnheadPredicate().returnHeadStr();
      headRelation = relations.find(rules.at(*it).returnheadPredicate().returnHeadStr())->second;
      rightHandPredicates = rules.at(*it).returnPredicates();
      //need to pass in predicates and a reference to tempRelation and a reference to rightHandRelations
      //maybe we only need to populate the database once
      populateDatabase(rightHandPredicates, tempRelation, rightHandRelations);//passes references to tempRelation and rightHandRelations to go through predicates a populate the database
      rightLen = rightHandRelations.size();
    //  cout << "number of right hand relations is " << rightLen << endl;
      /*while(rightLen > 1){ //joins until there is one tuple
        //cout << "Joining" << endl;
        rightHandRelations.at(0).join(rightHandRelations.at(1)); //combines the 1st and 2nd tuple
        rightHandRelations.erase(rightHandRelations.begin() + 1); //removes the 2nd tuple
        rightLen = rightHandRelations.size(); //updates length
      }*/
      joinRelations(rightLen, rightHandRelations);
      //cout << "Done joining" << endl;
      //Left of after finishing the join function, will have to name and project the relation,
      //then will perform a union with the relation tha matches the name of the new relation
      tempRelation = rightHandRelations.at(0);
      //tempRelation.printRows();
      tempRelation.setName(headId);
      /*for(auto&& param : rule.returnheadPredicate().getParameterString()){
        cout << param << " ";
      }
      cout << endl;*/
      tempRelation.project(rules.at(*it).returnheadPredicate().getParameterString());
      schema schemes = headRelation.returnSchemes();
      tempRelation.rename(schemes);
      //will need to create union and change output function for iterations
      newTuples = headRelation.Union(tempRelation);
      tempRelation.setRows(newTuples);
      relations.find(headId)->second = headRelation;
      //cout << "first iter" << endl;
      cout << tempRelation.ruleOutput();
      cout << "1 passes: R" << *it << endl;
}
else{
  cout << "SCC: ";
  //iterCount = 0;
  count = 0;
  oldSize = 0;
  /*while(it != tempSet.end()){
    if(iterCount <  componentLength - 1)
      cout << "R" << *it << ",";
    else
      cout << "R" << *it;
    iterCount++;
    ++it;
  }
  cout << endl;*/
  printRules(tempSet, componentLength);
  do{
    tupleAdded = false;
    it = tempSet.begin();
    for(it = tempSet.begin(); it != tempSet.end(); ++it){
    //for(it = stronglyConnectedComponents.at(i).begin(); it != stronglyConnectedComponents.at(i).end(); ++it){
      componentLength = tempSet.size();
      cout << rules.at(*it).toString() << endl;
      headId = rules.at(*it).returnheadPredicate().returnHeadStr();
      headRelation = relations.find(rules.at(*it).returnheadPredicate().returnHeadStr())->second;
      rightHandPredicates = rules.at(*it).returnPredicates();
      rightHandRelations.clear();
      //need to pass in predicates and a reference to tempRelation and a reference to rightHandRelations
      //maybe we only need to populate the database once
      populateDatabase(rightHandPredicates, tempRelation, rightHandRelations);//passes references to tempRelation and rightHandRelations to go through predicates a populate the database
      rightLen = rightHandRelations.size();
      /*while(rightLen > 1){ //joins until there is one tuple
        //cout << "Joining" << endl;
        rightHandRelations.at(0).join(rightHandRelations.at(1)); //combines the 1st and 2nd tuple
        rightHandRelations.erase(rightHandRelations.begin() + 1); //removes the 2nd tuple
        rightLen = rightHandRelations.size(); //updates length
      }*/
      joinRelations(rightLen, rightHandRelations);
      //cout << "Done joining" << endl;
      //Left of after finishing the join function, will have to name and project the relation,
      //then will perform a union with the relation tha matches the name of the new relation
      tempRelation = rightHandRelations.at(0);
      //tempRelation.printRows();
      tempRelation.setName(headId);
      /*for(auto&& param : rule.returnheadPredicate().getParameterString()){
        cout << param << " ";
      }
      cout << endl;*/
      tempRelation.project(rules.at(*it).returnheadPredicate().getParameterString());
      schema schemes = headRelation.returnSchemes();
      tempRelation.rename(schemes);
      //will need to create union and change output function for iterations
      newTuples = headRelation.Union(tempRelation);
      tempRelation.setRows(newTuples);
      output += tempRelation.ruleOutput();
      cout << tempRelation.ruleOutput();
      currentSize += headRelation.size();
      relations.find(headId)->second = headRelation;
    }
    if(oldSize < currentSize && output != ""){
      //cout << "Tuple added" << endl;
      tupleAdded = true;
    }
    oldSize = currentSize;
    currentSize = 0;
    output = "";
    count++;
      /*tempNode = dependencyGraph.getNode(*it);
      set<int>::iterator edgeIt;
      set<int> edges = tempNode.getEdges();
      if(componentLength <= 1)
        if(tempNode.getEdges().find(*it) == tempNode.getEdges().end()){
            cout << "first option" << endl;
        }
        if(componentLength <= 1 && edges.size() == 0){
          cout << "one iteration" <<  endl;
        }
        else{
          cout << "Fixed point algorithm" << endl;
        }*/
      /*  cout << "Edges for R" << *it << " :: ";
        for(edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt){
          //cout << 1 << endl;
          cout << *edgeIt << " ";
        }
        cout << endl;*/

      //cout << rules.at(*it).toString() << endl;
  } while(tupleAdded);
  cout << count <<  " passes: ";
  it = tempSet.begin();
  printRules(tempSet, componentLength);
}
};
void database::evaluateRules(vector<rule> rules){
  vector<relation> rightHandRelations;
  vector<predicate> rightHandPredicates;
  vector<string> variables;
  vector<string> parameters;
  set <Tuple> newTuples;
  set <int> columnsToProject;
  set<int>::iterator it;
  set<int> nodeEdges;
  relation tempRelation;
  relation headRelation;
  rule rule;
  predicate headPredicate;
  string headId = "";
  string predicateID = "";
  string s1 = "";
  string parameter = "";
  string output = "";
  node emptyNode;
  //bool matched;
  //for(auto&& rule : rules){ //will change to fixed point algorithm
  makeGraphs(rules);
  printDependencyGraph();
  cout << endl;
  dfsForest();
  findSCC();
  int sccSize = stronglyConnectedComponents.size();
  //int iterCount = 0;
  //int componentLength = 0;
  set<int> tempSet;
  node tempNode;
  cout << "Rule Evaluation" << endl;
  for(int i = 0; i < sccSize; i++){
    tempSet = stronglyConnectedComponents.at(i);
    rightHandPredicates.clear();
    rightHandRelations.clear();
    ruleEvaluation(tempSet, rightHandRelations, rightHandPredicates, rules);
  }
  cout << endl;
};
void checkFirstQueryParam(string &parameter, relation &outRelation, int &position, set<int> &columnsToProject, vector<string> &variables){
  if(parameter[0] == '\''){
    outRelation.select(position, parameter);
    //outRelation.printRows();
    position++;
  }
  else{//if the first param is a variable, we keep the entire relation and store the variable and variable position for output
    variables.push_back(parameter);
    columnsToProject.insert(position);
    //outRelation.printRows();
    position++;
  }
}
void database::evaluateQueries(vector<predicate> queries){ //for all evaluations should check to see if name exists before calling find
  string queryID = "";
  //cout << "QUERIES" << endl;
  int position = 0;
  relation outRelation;
  vector<string> parameters;
  vector<string> variables;
  vector <Tuple> outRows;
  schema outSchemes;
  set <int> columnsToProject;
  int len = 0;
  string parameter = "";
  string s1 = "";
  string s2 = "";
  bool matched = false;
  cout << "Query Evaluation" << endl;
  for(auto&& query : queries){//step through each query
    columnsToProject.clear();
    variables.clear();
    position = 0;
    queryID = query.returnHeadStr();
    //cout << queryID << endl;
    len = query.parametersLength();//only setting this once could speed things up marginally
    //relations.find(queryID)->second.printRows();
    parameters = query.getParameterString();
    parameter = parameters.at(position);
    outRelation = relations.find(queryID)->second;
    outRelation.setSchemes(parameters);
    checkFirstQueryParam(parameter, outRelation, position, columnsToProject, variables);
    //will change this loop to a function if need be
    while(position < len){
      parameter = parameters.at(position);
      matched = false;
      if(parameter[0] == '\''){
        outRelation.select(position, parameter);
        //outRelation.printRows();
      }
      else{
        for(int i = 0; i < position; i++){
          s1 = parameters.at(i);
          if(s1 == parameter){
            outRelation.select(i, position);
            //outRelation.printRows();
            matched = true;
          }
        }
        if(!matched){
          variables.push_back(parameter);
          columnsToProject.insert(position);
        }
      }
      position++;
    }
    outRelation.project(columnsToProject);
  //  if(variables.size() != 0)
      outRelation.rename(variables);
    cout << outRelation.toString();
    //outRelation.printRows();
  }
};
