#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include "tokType.h"

using namespace std;
class parameter{
  private:
    tokType type;
    string typeStr;
    string parameterStr;
    vector <string> parameters;
    //might need a vector for parameter contents
  public:
    parameter();
    string toString();
    void setTypeStr(tokType typeIn);
    void setParameter(string parameterIn);
    vector <string> returnParameters();
};
