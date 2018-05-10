#pragma once
#include <cstdlib>
#include "tokType.h"
#include <string>

using namespace std;

class token {
  private:
    tokType type;
    string value;
    int lineNumber;
  public:
    //token();
    void setType(tokType tokIn);
    void setVal(string valIn);
    void setLineNum(int numIn);
    tokType retType();
    string retVal();
    int retLineNum();
};
