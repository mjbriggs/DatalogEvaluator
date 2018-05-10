#include "predicate.h"
string predicate::toString(){
  string returnStr = "";
  int size = parameters.size();
  returnStr += headIDStr + "(";
  for(int i = 0; i < size; i++){
    if(i < size -1)
      returnStr +=  parameters.at(i).toString() + ",";
    else
      returnStr +=  parameters.at(i).toString();
  }
  returnStr += ")";
  return returnStr;
};
void predicate::setParameterList(parameter paramIn){
  parameters.push_back(paramIn);
  parametersString.push_back(paramIn.toString());
};
void predicate::clearParameterList(){
  parameters.clear();
  parametersString.clear();
};
void predicate::getHeadID(token tokenIn){
  headID = tokenIn;
  headIDStr = tokenIn.retVal();
};
token predicate::returnToken(){
  return headID;
}
string predicate::returnHeadStr(){
  return headIDStr;
}
string predicate::getParameter(int index){
  return parameters.at(index).toString();
};
int predicate::parametersLength(){
  return parameters.size();
};
vector <string> predicate::getParameterString(){
  return parametersString;
};
