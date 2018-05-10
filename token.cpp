#include "token.h"
void token::setType(tokType tokIn){
  type = tokIn;
};
void token::setVal(string valIn){
  value = valIn;
};
void token::setLineNum(int numIn){
  lineNumber = numIn;
};
tokType token::retType(){
  return type;
};
string token::retVal(){
  return value;
};
int token::retLineNum(){
  return lineNumber;
};
