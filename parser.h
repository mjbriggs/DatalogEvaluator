#pragma once
#include <cstdlib>
#include <vector>
#include "token.h"
#include "datalogProgram.h"
#include "parameter.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;
class parser{
  public:
    parser();
    void parse(vector<token> vectorIn, map<tokType, string> tokenMapIn);
    void match(tokType expected);
    string toString();
    void tokenInCheck();
    datalogProgram returnDatalogProgram();
  private:
    //datalogProgram object
    token currentToken;
    token prevToken;
    bool hasFailed;
    parameter param;
    string tempParamStr;
    predicate predicateObj;
    datalogProgram datalog;
    rule ruleObj;
    bool isQuery;
    bool isRule;
    bool isScheme;
    int index;
    int tokensLength;
    vector<token> parseTokens;
    map <tokType, string> parseTokenMap;
    void failure(token badToken);
    void scheme();
    void headPredicate();
    void idList();
    void schemeList();
    void factList();
    void fact();
    void stringList();
    void ruleParse();
    void ruleList();
    void predicateParse();
    void predicateList();
    void parameterParse();
    void expressionParameters();
    void expression();
    void operators();
    void parameterList();
    void queryList();
    void query();
};
