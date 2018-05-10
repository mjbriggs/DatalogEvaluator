#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include "predicate.h"

using namespace std;
class rule{
  private:
    predicate headPredicate;
    vector<predicate> predicates;
  public:
    void setHeadPredicate(predicate headPredicateIn);
    void addPredicates(predicate predicateIn);
    void clearRule();
    vector<predicate> returnPredicates();
    predicate returnheadPredicate();
    string toString();
};
