#include "parser.h"

parser::parser(){
  index = 0;
  tokensLength = 0;
  hasFailed = false;
  isQuery = false;
  isRule = false;
  isScheme = false;
};
void parser::parse(vector<token> vectorIn, map<tokType, string> tokenMapIn){
//  bool hasFailed = false;
  parseTokens = vectorIn;
  tokensLength = parseTokens.size();
  parseTokenMap = tokenMapIn;
  currentToken = parseTokens.at(index);
  try{
    //cout << "index :: " << index << endl;
    match(SCHEMES);
    //cout << "index :: " << index << endl;
    match(COLON);
    scheme();
    schemeList();
    match(FACTS);
    match(COLON);
    factList();
    match(RULES);
    match(COLON);
    ruleList();
    match(QUERIES);
    match(COLON);
    queryList();
    match(EoF);
  }
  catch(token badToken){
    //failure(badToken);
  }
  if(!hasFailed){
    //cout << "Success!" << endl;
    //cout << datalog.toString();
  }
  //cout << parseTokens.at(index).retType();
  //cout << "\nIndex :: " << index <<  " and Length :: " << tokensLength << endl;
};
datalogProgram parser::returnDatalogProgram(){
  return datalog;
};
void parser::match(tokType expected){
  tokType currentTokenType = currentToken.retType();
  //cout << parseTokenMap.find(currentTokenType)->second << endl;
  if(currentTokenType == expected){
    if(currentTokenType != EoF){
      prevToken = currentToken;
        index++;
    }
    //cout << parseTokenMap.find(currentTokenType)->second;
  //  cout << "\nIndex :: " << index <<  " and Length :: " << tokensLength << endl;
    currentToken = parseTokens.at(index);
  }else{
    throw currentToken;
  }
};

/* now working == expression in expressions
ID after a closed paren in rules after expression*/
//string parser::toString(){};
void parser::tokenInCheck(){
  string tokenString = "";
  tokenString = "(";
  token temp;
  tokType tempType;
  int tempLineNum = 0;
  cout << "\n\nparser vector check\n" << endl;
  for(int i = 0; i < tokensLength; ++i){
    temp = parseTokens.at(i);
    tempType = temp.retType();
    tempLineNum = temp.retLineNum();
    tokenString += parseTokenMap.find(tempType)->second;
    tokenString += ",\"" + temp.retVal() + "\",";
    //tokenString += tempLineNum + ")";
    cout << tokenString << tempLineNum << ")" << endl;
    tokenString = "(";
  }
  cout << "Total Tokens = " << tokensLength;
};
void parser::failure(token badToken){
   hasFailed = true;
   cout << "Failure!" << endl;
   tokType badTokenType = badToken.retType();
   cout << "  (" << parseTokenMap.find(badTokenType)->second << ",\"" << badToken.retVal() <<
   "\"," << badToken.retLineNum() << ")\n" << endl;
};
void parser::scheme(){
  isScheme = true;
  headPredicate();
  isScheme = false;
};
void parser::headPredicate(){
    predicateObj.getHeadID(currentToken);
    match(ID);
    match(LEFT_PAREN);
    param.setParameter(currentToken.retVal());
    predicateObj.setParameterList(param);
    match(ID);
    idList();
    match(RIGHT_PAREN);
    if(isScheme)
      datalog.addScheme(predicateObj);
    else if(isRule)
      ruleObj.setHeadPredicate(predicateObj);
  //  cout << "predicateObj:: " << predicateObj.toString() << endl;
    predicateObj.clearParameterList();
};
void parser::idList(){
  if(currentToken.retType() == COMMA){
    match(COMMA);
    param.setParameter(currentToken.retVal());
    predicateObj.setParameterList(param);
    match(ID);
    idList();
  }
  else{
    return;
  }
};
void parser::schemeList(){
  if(currentToken.retType() == ID){
    scheme();
    schemeList();
  }
  else{
    return;
  }
}
void parser::factList(){
  if(currentToken.retType() == ID){
    fact();
    factList();
  }
  else{
    //failure(currentToken);
    return;
  }
};
void parser::fact(){
  predicateObj.getHeadID(currentToken);
  match(ID);
  match(LEFT_PAREN);
  param.setParameter(currentToken.retVal());
  predicateObj.setParameterList(param);
  datalog.addDomain(currentToken.retVal());
  match(STRING);
  stringList();
  match(RIGHT_PAREN);
  match(PERIOD);
  datalog.addFact(predicateObj);
  predicateObj.clearParameterList();
};
void parser::stringList(){
  if(currentToken.retType() == COMMA){
    match(COMMA);
    param.setParameter(currentToken.retVal());
    predicateObj.setParameterList(param);
    datalog.addDomain(currentToken.retVal());
    match(STRING);
    stringList();
  }
  else{
    return;
  }
};
void parser::ruleList(){
  if(currentToken.retType() == ID){
    ruleParse();
    ruleList();
  }
  else{
    return;
  }
};
void parser::ruleParse(){
  isRule = true;
  headPredicate();
  match(COLON_DASH);
  predicateParse();
  predicateList();
  //  cout << " rules :: " + ruleObj.toString() << endl;
  match(PERIOD);
  datalog.addRule(ruleObj);
  ruleObj.clearRule();
  isRule = false;
};
void parser::predicateList(){
  if(currentToken.retType() == COMMA){
    match(COMMA);
    predicateParse();
    predicateList();
  }
  else{
    return;
  }
};
void parser::predicateParse(){
  predicateObj.getHeadID(currentToken);
  match(ID);
  match(LEFT_PAREN);
  parameterParse();
  parameterList();
  match(RIGHT_PAREN);
  //cout << "predicateObj :: " << predicateObj.toString() << endl;
  if(isQuery)
    datalog.addQuery(predicateObj);
  else if(isRule)
      ruleObj.addPredicates(predicateObj);
  predicateObj.clearParameterList();
};
void parser::parameterList(){
  if(currentToken.retType() == COMMA){
    match(COMMA);
    parameterParse();
    parameterList();
    //cout << "parameterList :: " << param.toString() << endl;
  }
  else{
    return;
  }

};//creating a parameter object everytime a match is called
void parser::parameterParse(){
  /*if(currentToken.retType() == RIGHT_PAREN){
    //failure(currentToken);
    throw currentToken;
    return;
  }*/
  if(currentToken.retType() == STRING){
  //  parameter.setTypeStr(currentToken.retType());
    param.setParameter(currentToken.retVal());
    predicateObj.setParameterList(param);
    //tempParamStr += currentToken.retVal();
    match(STRING);
  }
  else if(currentToken.retType() == ID){
  //  parameter.setTypeStr(currentToken.retType());
    param.setParameter(currentToken.retVal());
    predicateObj.setParameterList(param);
    //tempParamStr += currentToken.retVal();
    match(ID);
  }
  else if(currentToken.retType() == LEFT_PAREN){
    tempParamStr = "";
    expression();
    param.setParameter(tempParamStr);
    predicateObj.setParameterList(param);
  }
  else{
    throw currentToken;
    return;
  }
};
void parser::expressionParameters(){//puts entire expresion into a string
  //cout << "in expressionParameters" << endl;
  //token prevToken =
  if(prevToken.retType() == RIGHT_PAREN)// && (prevToken != ID || prevToken !+ STRING))
    return;
  if(currentToken.retType() == STRING){
    tempParamStr += currentToken.retVal();
  //  cout << "Current token ::: " << currentToken.retVal() << endl;
  //cout << "Expression tempParamStr :: " << currentToken.retVal() << endl;
    match(STRING);
  }
  else if(currentToken.retType() == ID){
    tempParamStr += currentToken.retVal();
  //  cout << "Current token ::: " << currentToken.retVal() << endl;
    //cout << "Expression tempParamStr :: " << currentToken.retVal() << endl;
    match(ID);
  }
  else if(currentToken.retType() == LEFT_PAREN){
    //tempParamStr = "";
    ////cout << "Current token ::: " << currentToken.retVal() << endl;
    //cout << "tempParamStr :: " << currentToken.retVal() << endl;
    expression();
    param.setParameter(tempParamStr);
  }
  else{
    throw currentToken;
    return;
  }
};
void parser::expression(){
  //cout << "in expression" << endl;
  tempParamStr += currentToken.retVal();
  match(LEFT_PAREN);
  expressionParameters();
  operators();
  expressionParameters();
  tempParamStr += currentToken.retVal();
  //cout << "tempParamStr :: " << currentToken.retVal() << endl;
  match(RIGHT_PAREN);
};
void parser::operators(){
  //cout << "in operators" << endl;
  if(currentToken.retType() == ADD){
    //param.setParameter(currentToken.retVal());
    tempParamStr += currentToken.retVal();
    //cout << "Current token ::: " << currentToken.retVal() << endl;
    match(ADD);
  }
  else if(currentToken.retType() == MULTIPLY){
    //param.setParameter(currentToken.retVal());
    tempParamStr += currentToken.retVal();
    //cout << "Current token ::: " << currentToken.retVal() << endl;
    match(MULTIPLY);
  }
  else{
    return;
  }
};
void parser::queryList(){
  if(currentToken.retType() == ID){
    query();
    queryList();
  }
  else{
    return;
  }
};
void parser::query(){
  isQuery = true;
  predicateParse();
  match(Q_MARK);
  isQuery = false;
  /*if(currentToken.retType() == EoF){
    match(EoF);
  }*/
};
