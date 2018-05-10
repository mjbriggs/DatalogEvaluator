#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <sstream>
#include "predicate.h"
#include "rule.h"

using namespace std;
class datalogProgram{
  private:
    vector<predicate> schemes;
    vector<predicate> queries;
    vector<predicate> facts;
    vector<rule> rules;
    set<string> domain;
  public:
    void addScheme(predicate predicateIn);
    void addFact(predicate predicateIn);
    void addQuery(predicate predicateIn);
    void addRule(rule ruleIn);
    void addDomain(string domainIn);
    vector<predicate> returnSchemes();
    vector<predicate> returnFacts();
    vector<predicate> returnQueries();
    vector<rule> returnRules();
    string toString();
};
