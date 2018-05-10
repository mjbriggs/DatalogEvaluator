#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include "token.h"
#include "parameter.h"

using namespace std;
class predicate{
  private:
    token headID;
    string headIDStr;
    vector <parameter> parameters;
    vector <string> parametersString;
    //parameter param;
  public:
    string toString();
    void setParameterList(parameter paramIn);
    void clearParameterList();
    void getHeadID(token tokenIn);
    token returnToken();
    string returnHeadStr();
    string getParameter(int index);
    int parametersLength();
    vector <string> getParameterString();
    //need to grab headId
};
