#include "datalogProgram.h"
void datalogProgram::addScheme(predicate predicateIn){
  schemes.push_back(predicateIn);
};
void datalogProgram::addFact(predicate predicateIn){
  facts.push_back(predicateIn);
};
void datalogProgram::addQuery(predicate predicateIn){
  queries.push_back(predicateIn);
};
void datalogProgram::addRule(rule ruleIn){
  rules.push_back(ruleIn);
};
void datalogProgram::addDomain(string domainIn){
  domain.insert(domainIn);
};
vector<predicate> datalogProgram::returnSchemes(){
  return schemes;
};
vector<predicate> datalogProgram::returnFacts(){
  return facts;
};
vector<predicate> datalogProgram::returnQueries(){
  return queries;
};
vector<rule> datalogProgram::returnRules(){
  return rules;
};

string datalogProgram::toString(){
  set<string>::iterator it;
  int size = 0;
  stringstream ss;
  string returnStr = "";
  size = schemes.size();
  ss << "Schemes(" << size << "):\n";
  for(int i = 0; i < size; i++){
    ss << "  " <<  schemes.at(i).toString() << "\n";
  }
  size = facts.size();
  ss <<  "Facts(" << size << "):\n";
  for(int i = 0; i < size; i++){
    ss <<  "  " << facts.at(i).toString() << ".\n";
  }
  size = rules.size();
  ss <<   "Rules(" << size << "):\n";
  for(int i = 0; i < size; i++){
     ss <<  "  " << rules.at(i).toString() << ".\n";
  }
  size = queries.size();
  ss <<   "Queries(" << size << "):\n";
  for(int i = 0; i < size; i++){
     ss <<  "  " << queries.at(i).toString() << "?\n";
  }
  size = domain.size();
  ss <<   "Domain(" << size << "):\n";
  for(it = domain.begin(); it != domain.end(); ++it){
    ss << "  " <<  *it << "\n";
  }
  return ss.str();
};
