#include "rule.h"
void rule::setHeadPredicate(predicate headPredicateIn){
  headPredicate = headPredicateIn;
};
void rule::addPredicates(predicate predicateIn){
  predicates.push_back(predicateIn);
  //cout << predicates.back().toString() << endl;
};
string rule::toString(){
  string returnStr = "";
  int size = predicates.size();
  returnStr += headPredicate.toString() + " :- ";
  for(int i = 0; i < size; i++){
    if(i < size -1)
      returnStr += predicates.at(i).toString() + ",";
    else
      returnStr += predicates.at(i).toString();
  }
  return returnStr;
};
void rule::clearRule(){
  predicates.clear();
};
vector<predicate> rule::returnPredicates(){
  return predicates;
};
predicate rule::returnheadPredicate(){
  return headPredicate;
};
