#include "relation.h"

relation::relation(){
  name = "";

};
void relation::select(int &position, string &value){
  set<Tuple> newTuples;
  set<Tuple>::iterator it;
  for(it = rows.begin(); it != rows.end(); ++it){
    if(it->at(position) == value){
      newTuples.insert(*it);
    }
  }
  rows = newTuples;
};
void relation::select(int &position1, int &position2){
  set<Tuple> newTuples;
  set<Tuple>::iterator it;
  for(it = rows.begin(); it != rows.end(); ++it){
    if(it->at(position1) == it->at(position2)){
      newTuples.insert(*it);
    }
  }
  rows = newTuples;
};
void relation::project(const set<int> &include){
  set <Tuple> projectedColumns;
  Tuple addTuple;
  set<Tuple>::iterator it;
  int tupleLen = 0;
  for(it = rows.begin(); it != rows.end(); ++it){
    tupleLen = it->size();
    for(int i = 0; i < tupleLen; i++){
      if(include.find(i) != include.end()){
        addTuple.push_back(it->at(i));
      }
    }
    projectedColumns.insert(addTuple);
    addTuple.clear();
  }
  rows = projectedColumns;
  /*int len = rows.size();
  int tupleLen = rows.find(0).size();
  //cout << "columns :: " << endl;
  for(int i = 0; i < len; i++){
    addTuple.clear();
    for(int j = 0; j < tupleLen; j++){
      if(include.find(j) != include.end()){
        //cout << rowsIn.at(i).at(j) << endl;
        addTuple.push_back(rows.find(i).at(j));
      }
    }
    projectedColumns.insert(addTuple);
  }*/
  rows = projectedColumns;
  /*for(it = include.begin(); it != include.end(); ++it){
    cout << *it << " " ;
  }*/
  //cout << endl;
};
int found(const schema &schemes, const string &searchVal){
  int schemeLen = schemes.size();
  string scheme = "";
  //cout << "finding match" << endl;
  for(int i = 0; i < schemeLen; i++){
    scheme = schemes.at(i);
    if(scheme == searchVal)
      return i;
  }
  return -1;
}
void relation::project(const vector<string> &includeSchemes){//I think that the projection works now, need to make sure tho since I haven't renamed yet
  set<Tuple> projectedColumns;
  set<Tuple>::iterator it;
  Tuple addTuple;
  //cout << "schemes to include " << endl;
  /*for(auto&& IS : includeSchemes){
    cout << IS << " ";
  }
  cout << endl;
  cout << "current schems " << endl;
  for(auto&& IS : schemes){
    cout << IS << " ";
  }
  this->printRows();
  cout << endl;*/
  int includeLength = includeSchemes.size();
  //int rowLength = rows.size();
  //int rowLength = schemes.size();
  int foundIndex = -1;
  //cout << "projecting schemes" << endl;
  for(it = rows.begin(); it != rows.end(); ++it){
    addTuple.clear();
    for(int i = 0; i < includeLength; i++){
      foundIndex = found(schemes, includeSchemes.at(i));
      if(foundIndex != -1){
        //cout << "foundIndex " << foundIndex << " Length " << rowLength << endl;
        //cout << "Pushing value " << endl;
        addTuple.push_back(it->at(foundIndex));
      }
    }
    //cout << "inserting value " << endl;
    projectedColumns.insert(addTuple);
  }
  rows = projectedColumns;
};

void relation::rename(vector<string> &params){
  schema newSchemes;
  int len = params.size();
  for(int i = 0; i < len; i++){
    newSchemes.push_back(params.at(i));
  }
  //for(int j = 0; j < len; j++){
    //cout << newSchemes.at(j) << endl;
  //}
  schemes = newSchemes;
};
void relation::rename(schema &params){
  schema newSchemes;
  int len = params.size();
  for(int i = 0; i < len; i++){
    newSchemes.push_back(params.at(i));
  }
  //for(int j = 0; j < len; j++){
    //cout << newSchemes.at(j) << endl;
  //}
  schemes = newSchemes;
}; //might not need to change this one

bool joinable(schema &s1, schema &s2, const Tuple &t1, const Tuple &t2){
  int t1Length = t1.size();
  int t2Length = t2.size();
  for(int i = 0; i < t1Length; i++){
    for(int j = 0; j < t2Length; j++){
      if(s1[i] == s2[j] && t1[i] != t2[j])
        return false;
    }
  }
  return true;
};
Tuple relation::combineTuples(const Tuple &t1, const Tuple &t2, schema &s1, schema &s2){
  Tuple combined = t1;
  bool match = false;
  int t1Len = t1.size();
  int t2Len = t2.size();
  //for(auto&& scheme2 : s2){
  for(int i = 0; i < t2Len; i++){
    match = false;
    //for(auto&& scheme1 : s1){
    for(int j = 0; j < t1Len; j++){
      if(s2.at(i) == s1.at(j)){
        //cout << "match at " << s2.at(i) << " and " << s1.at(j) << endl;
        match = true;
      }
    }
    if(!match){
      //cout << "adding " << val2 << endl;
      //cout << "adding at " << i << endl;
      combined.push_back(t2.at(i));
    }
  }
  return combined;
};
schema relation::joinSchemes(schema &rInSchemes){
  schema newSchemes;
  newSchemes = schemes;
  bool match;
  for(auto&& schema : rInSchemes){ // here we are creating new schemes for the relation
    match = false;
    for(auto&& name : newSchemes){
      if(name == schema){
        match = true;
      }
    }
    if(!match){
      newSchemes.push_back(schema); // if scheme is unique, add it to the new scheme
    }
  }
  return newSchemes;
}
void relation::join(relation &rIn){
  relation newRelation;
  schema rInSchemes = rIn.returnSchemes();
  //bool match;
  //cout << "Joining "<< name << " and " << rIn.getName() << endl;
  //cout << name << " :: " << endl;
  //this->printRows();
  //cout << rIn.getName() << " :: " << endl;
  //rIn.printRows();
  newRelation.setSchemes(joinSchemes(rInSchemes));
  //now we begin the join process
  //for(int i = 0; i < )
  for(auto&& t1 : rows){
    //match = false;
    for(auto&& t2 : rIn.returnRows()){
      if(joinable(schemes, rInSchemes, t1, t2)){
        newRelation.setTuple(combineTuples(t1, t2, schemes, rInSchemes));
      }
    }
  }
  //newRelation.printRows();
  schemes = newRelation.returnSchemes();
  rows = newRelation.returnRows();
};

set<Tuple> relation::Union(relation &rIn){
  //make new tuple
  //if scheme for rIn matched scheme for relation, add value to tuple
  //push tuple in to rows
  //clear tuple
  set<Tuple> newRows;
  if(rIn.returnSchemes() == schemes){
    //cout << "compatible" << endl;
    for(auto&& newRow : rIn.returnRows()){
      if(rows.insert(newRow).second){
        newRows.insert(newRow);
      }
    }
  }
  return newRows;
};

schema relation::returnSchemes(){
  return schemes;
};
void relation::setName(const string &nameIn){
  //name = "A";
    name = nameIn;
  //  cout << name << ' ' << schemes.size() << endl;
};
void relation::setSchemes(const schema &schemesIn){
  schemes = schemesIn;
};

void relation::setSchemes(const vector <string> &parameters){
  originalSchemes.clear();
  int length = parameters.size();
  for(int i = 0; i < length; i++){
    //cout << parameters.at(i) << " ";
    schemes.push_back(parameters.at(i));
    originalSchemes.push_back(parameters.at(i));
  }
  //printSchema();
};
void relation::printSchema(){
  int length = schemes.size();
  for(int i = 0; i < length; i++){
    cout << schemes.at(i) << endl;
  }
}
void relation::setTuple(const Tuple &tIn){
  rows.insert(tIn);
};
void relation::setTuple(const vector<string> &parameters){
/*  if(!duplicateTuple(parameters)){
    int length = parameters.size();
    Tuple tempTuple;
    for(int i = 0; i < length; i++){
      tempTuple.push_back(parameters.at(i));
      //cout << parameters.at(i) << endl;
    }
    //rows.insert(tempTuple);
    rowVec.push_back(tempTuple);
  }
  else{
    //cout << "tuple not added" << endl;
  }*/
  int length = parameters.size();
  Tuple tempTuple;
  for(int i = 0; i < length; i++){
    tempTuple.push_back(parameters.at(i));
    //cout << parameters.at(i) << endl;
  }
  rows.insert(tempTuple);
};

void relation::setRows(set<Tuple> &rowsIn){
  rows = rowsIn;
};

/*bool relation::duplicateTuple(vector<string> parameters){
  int len = rowVec.size();
  //cout << "checking for duplicates" << endl;
  for(int i = 0; i < len; i++){
    //cout << rowVec.at(i).toString() << endl;
    if(rowVec.at(i).isDuplicate(parameters)){
      return true;
    }
  }
  return false;
};*/
/*vector<Tuple> relation::returnRows(){
  return rowVec;
};*/
set<Tuple> relation::returnRows(){
  return rows;
}
void relation::printRows(){
  set<Tuple>::iterator it;
  int count = 0;
  int rowLen = 0;
  cout << "set" << endl;
  for (it=rows.begin(); it!=rows.end(); ++it){
    rowLen = it->size();
    for(int j = 0; j < rowLen; j++){
      cout << it->at(j) << " ";
    }
    cout << endl;
    //cout << count << it->toString();
    count ++;
  }
  /*std::vector<Tuple>::iterator it;
  it = std::unique (rowVec.begin(), rowVec.end());
  rowVec.resize( std::distance(rowVec.begin(),it) );
  sort(rowVec.begin(), rowVec.end());
  rowVec.erase(unique(rowVec.begin(), rowVec.end()), rowVec.end());*/
  // using predicate comparison:
  //std::unique (rowVec.begin(), rowVec.end(), myfunction);   // (no changes)

  /*int len = rowVec.size();
  int rowLen = 0;
  cout << name << endl;
  for(int i = 0; i < len; i++){
    rowLen = rowVec.at(i).
    cout << rowVec.at(i).toString();
  }*/
};
string relation::toString(){
  stringstream ss;
  int paramLen = originalSchemes.size();
  int rowLen = 0;
  ss << name << "(";
  for(int i = 0; i < paramLen; i++){
    if(i < paramLen - 1){
      ss << originalSchemes.at(i) << ",";
    }
    else{
      ss << originalSchemes.at(i) << ")? ";
    }
  }
  if(rows.size() != 0){
    ss << "Yes(" << rows.size() << ")\n";
    set<Tuple>::iterator it;
    for(it = rows.begin(); it != rows.end(); ++it){
      rowLen = it->size();
      for(int i = 0; i < rowLen; i++){
        if(i == 0)
          ss << "  ";
        if(i < rowLen - 1)
          ss << schemes.at(i) << "=" << it->at(i) << ", ";
        else
          ss << schemes.at(i) << "=" << it->at(i) << "\n";
      }
    }
  }
  else{
    ss << "No\n";
  }
  return ss.str();
};

string relation::ruleOutput(){
  stringstream ss;
  //int paramLen = originalSchemes.size();
  int rowLen = 0;
    set<Tuple>::iterator it;
    for(it = rows.begin(); it != rows.end(); ++it){
      rowLen = it->size();
      for(int i = 0; i < rowLen; i++){
        if(i == 0)
          ss << "  ";
        if(i < rowLen - 1)
          ss << schemes.at(i) << "=" << it->at(i) << ", ";
        else
          ss << schemes.at(i) << "=" << it->at(i) << "\n";
      }
    }
  return ss.str();
};

int relation::size(){
  return rows.size();
};

string relation::getName(){
  return name;
};
