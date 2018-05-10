#include "parameter.h"
parameter::parameter(){
  parameterStr = "";
  typeStr = "";
}
string parameter::toString(){
  //will output parameter, will then reset parameterStr
  /*int size = parameters.size();
  for(int i = 0; i < size; i++){
    parameterStr += parameters.at(i);
    if(parameters.at(i) != "(" || parameters.at(i) != ")"){
      parameterStr += ",";
    }
  }*/
  string returnStr = parameterStr;
  //parameters.clear();
  return returnStr;
};
void parameter::setTypeStr(tokType typeIn){
  type = typeIn;
};
void parameter::setParameter(string parameterIn){
  parameterStr = parameterIn;
  //parameters.push_back(parameterIn);
};
vector <string> parameter::returnParameters(){
  return parameters;
};
