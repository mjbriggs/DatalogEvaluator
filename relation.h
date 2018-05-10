#pragma once
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>    // std::unique, std::distance
#include "schema.h"
#include "tuple.h"

using namespace std;
class relation {
  private:
    string name;
    schema originalSchemes;
    schema schemes;
    set<Tuple> rows;
    vector<Tuple> rowVec;
    vector<Tuple> returnVec;
  public:
    relation();
    //new operations with relation
    void select(int &position, string &value);
    //vector<Tuple> select(int position, string value, vector<Tuple> rowsIn);
  //  vector<Tuple> select(int position1, int position2);
    void select(int &position1, int &position2);
    void project(const set<int> &include);//will need to be able to change the order of the columns for the next project
    void project(const vector<string> &includeSchemes);
    void rename(vector<string> &params); //might not need to change this one
    void rename(schema &params); //might not need to change this one
    void join(relation &rIn); //too complex
    schema joinSchemes(schema &rInSchemes);
    set<Tuple> Union(relation &rIn);
    //end of new operations
    void setName(const string &nameIn);
    void setSchemes(const vector <string> &parameters);
    void setSchemes(const schema &schemesIn);
    void setTuple(const vector<string> &parameters);
    void setTuple(const Tuple &tIn);
    void setRows(set<Tuple> &rowsIn);
  //  bool duplicateTuple(vector<string> parameters);
    void printSchema();
    void printRows();
    int size();
    schema returnSchemes();
    string getName();
    Tuple combineTuples(const Tuple &t1, const Tuple &t2, schema &s1, schema &s2);
    set<Tuple> returnRows();
    string toString();
    string ruleOutput();
    //vector<Tuple> returnRows();
};
