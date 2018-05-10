#include "scanner.h"
scanner::scanner(){
  keywords[0] = "Schemes";
  keywords[1] = "Facts";
  keywords[2] = "Rules";
  keywords[3] = "Queries";
  vecLength = 0;
  lineCount = 1;
  keywordLen = 4;
  tokStr = "";
  stringStr = "";
  commentStr = "";
  loadMap();
};
void scanner::scanFile(ifstream& fin){
  //string stringStr = "";
  //string tokStr = "";
  //string commentStr = "";
  char c;
  char vecChar;
  int vecLength;
  //int eofLineCt = 0;
  while(fin.get(c)){
    inputChars.push_back(c);
  }
  vecLength = inputChars.size();
  ////cout << vecLength;
  for(int i = 0; i < vecLength; i++){
    vecChar = inputChars.at(i);
    if(vecChar == '\n'){
      lineCount++;
    }
    if(!checkChars(vecChar, i)){//if none of the basic characters are found, look for strings,comments and ID's
      switch(vecChar){
        case '\'':
          stringCheck(vecChar, i, vecLength);
          break;
        case '#':
          commentCheck(vecChar, i);
          break;
        default:
          keywordAndIDCheck(vecChar, i);
        break;
      }
    }
  }
  pushToken(EoF, "", lineCount);
};
void scanner::loadMap(){
  tokenMap[COMMA] = "COMMA";
  tokenMap[PERIOD] = "PERIOD";
  tokenMap[Q_MARK] = "Q_MARK";
  tokenMap[LEFT_PAREN] = "LEFT_PAREN";
  tokenMap[RIGHT_PAREN] = "RIGHT_PAREN";
  tokenMap[COLON] = "COLON";
  tokenMap[COLON_DASH] = "COLON_DASH";
  tokenMap[MULTIPLY] = "MULTIPLY";
  tokenMap[ADD] = "ADD";
  tokenMap[SCHEMES] = "SCHEMES";
  tokenMap[FACTS] = "FACTS";
  tokenMap[RULES] = "RULES";
  tokenMap[QUERIES] = "QUERIES";
  tokenMap[ID] = "ID";
  tokenMap[STRING] = "STRING";
  tokenMap[COMMENT] = "COMMENT";
  tokenMap[UNDEFINED] = "UNDEFINED";
  tokenMap[EoF] = "EOF";

};
void scanner::printScanner(){
  string tokenString = "";
  int tokLength = 0;
  int tempLineNum = 0;
  tokenString = "(";
  token temp;
  tokType tempType;
  tokLength = tokens.size();
  ////cout << endl;
  for(int i = 0; i < tokLength; i++){
    temp = tokens.at(i);
    tempType = temp.retType();
    tempLineNum = temp.retLineNum();
    tokenString += tokenMap.find(tempType)->second;
    tokenString += ",\"" + temp.retVal() + "\",";
    //tokenString += tempLineNum + ")";
    cout << tokenString << tempLineNum << ")" << endl;
    tokenString = "(";
  }
  cout << "Total Tokens = " << tokLength;
};
vector <token> scanner::returnTokens(){
  return tokens;
};
int scanner::pushCharToken(char valIn, int index){
  string stringVal = "";
  stringVal += valIn;
  scannerToken.setVal(stringVal);
  scannerToken.setLineNum(lineCount);
  switch (valIn) {
    case ',':
    scannerToken.setType(COMMA);
    break;
    case '.':
      scannerToken.setType(PERIOD);
      break;
    case '?':
      scannerToken.setType(Q_MARK);
      break;
    case '(':
      scannerToken.setType(LEFT_PAREN);
      break;
    case ')':
      scannerToken.setType(RIGHT_PAREN);
      break;
    case ':':
      if(index != (vecLength - 1)){
        if(inputChars.at(index + 1) == '-'){
          scannerToken.setVal(":-");
          scannerToken.setLineNum(lineCount);
          scannerToken.setType(COLON_DASH);
          index++;
        }
        else{
          scannerToken.setType(COLON);
        }
        break;
      }
      else{
        scannerToken.setType(COLON);
      }
      break;
    case '*':
      scannerToken.setType(MULTIPLY);
      break;
    case '+':
      scannerToken.setType(ADD);
      break;
    default:
    break;
  }
  tokens.push_back(scannerToken);
  return index;
};
void scanner::pushToken(tokType typeIn, string valIn, int lineIn){
  scannerToken.setType(typeIn);
  scannerToken.setVal(valIn);
  scannerToken.setLineNum(lineIn);
  tokens.push_back(scannerToken);
};
bool scanner::checkChars(char c, int &i){
  bool found = false;
  switch(c){
    case ',':
      pushCharToken(',', i);
      found = true;
      break;
    case '.':
      pushCharToken('.', i);
      found = true;
      break;
    case '?':
      pushCharToken('?', i);
      found = true;
      break;
    case '(':
      pushCharToken('(', i);
      found = true;
      break;
    case ')':
      pushCharToken(')', i);
      found = true;
      break;
    case ':':
      i = pushCharToken(':',i); //checks for ':' and ':-'
      found = true;
      break;
    case '*':
      pushCharToken('*', i);
      found = true;
      break;
    case '+':
      pushCharToken('+', i);
      found = true;
      break;
      default:
      break;
    }
    return found;
};
void scanner::keywordAndIDCheck(char c, int i){
  bool match;
  string temp;
  string undefinedChar = "";
  temp = "";
  match = false;
  if(isalnum(c)){
    tokStr += c;
    ////cout <<"tokstr " << tokStr << endl;
    scanID(tokStr,i,vecLength);//scans for ID if eof
    /*if(i == (vecLength - 1)){
      if(isalpha(tokStr[0])){
        pushToken(ID, tokStr, lineCount);
        tokStr = "";
      }
    }*///this else if checks to see if the token is any of the keywords
    if(!isalnum(inputChars.at(i + 1))){
      if(isalpha(tokStr[0])){
        for(int j = 0; j < keywordLen; j ++){
          temp = keywords[j];
          if(tokStr == temp){
            match = true;
          }
        }
        if(!match){
          pushToken(ID, tokStr, lineCount);
          tokStr = "";
        }
      }
      scanKeyWord(tokStr);
    }
    return;
  }
  //else{
    if(!iswspace(c)){
      undefinedChar += c;
      pushToken(UNDEFINED, undefinedChar, lineCount);
    }
  //}
};

void scanner::stringCheck(char c, int &i, int length){
  int stringLen;
  int lineAdd;
  lineAdd = 0;
  stringStr += c;
  if(checkIndex(i, length)){
    i++;
    c = inputChars.at(i);
    ////cout << i << endl;
    while((i != (length -1))){
      if(c == '\n'){
        lineAdd++;
      }
      if(c == '\''){
        if(inputChars.at(i + 1) == '\''){
          stringStr += c;
          i++;
          c = inputChars.at(i);
        }
        else{
          break;
        }
      }
      stringStr += c;
      i++;
    //  //cout << length << endl;
      //if(i == length){
        //  //cout << i << endl;
      //}
      c = inputChars.at(i);
    }
    stringStr += c;
    stringLen = stringStr.length();
    if(stringStr[stringLen - 1] == '\''){
      pushToken(STRING, stringStr, lineCount);
      stringStr = "";
      lineCount += lineAdd;
    }
    else{
      pushToken(UNDEFINED, stringStr, lineCount);
      stringStr = "";
      i--;
      lineCount += lineAdd;
    }
  }
  else{
    pushToken(UNDEFINED, stringStr, lineCount);
    stringStr = "";
  }
};
void scanner::commentCheck(char c, int &i){
  int commentLineAdd;
  commentLineAdd = 0;
  //int commentLen;
  commentStr += c;
  vecLength = inputChars.size();
  if(i != (vecLength - 1)){
    i++;
    c = inputChars.at(i);
    if(c == '|'){
      //cout << vecLength;
      blockComment(commentStr, c, vecLength, i, commentLineAdd); // pushes block comment into token vector if comment is valid
    }
    else{
      while((c != '\n') && (i != (vecLength -1))){
        commentStr += c;
        i++;
        c = inputChars.at(i);
      }
    //  pushToken(COMMENT, commentStr, lineCount);
      commentStr = "";
      lineCount++;
    }
  }
};
bool scanner::checkIndex(int i, int length){
  if(i < length){
    return true;
  }
  return false;
};
void scanner::pushComment(string &str, int lineToAdd){
  int commentLen = str.length();
  if((str[commentLen - 1] == '#') && (str[commentLen - 2] == '|')){
    pushToken(COMMENT, str, lineCount);
    str = "";
    lineCount += lineToAdd;
  }
  else{
    pushToken(UNDEFINED, str, lineCount);
    str = "";
    lineCount += lineToAdd;
  }
};
void scanner::blockComment(string &str, char c, int length, int &i, int &commentLineAdd){
  char prev;
  str += c;
//  int commentLen;
  //commentLen = 0;
  //cout << length;
  if(i != (length -1)){
    prev = c;
    i++;
    c = inputChars.at(i);
    ////cout << " prev " << prev << " and c " << c << endl;
    while(((prev != '|') || (c != '#')) && (i != (length - 1))){
      //cout << " prev " << prev << " and c " << c << endl;
      //cout << "in loop while i = " << i << endl;
      str += c;
      if(c == '\n'){
        commentLineAdd++;
      }
      prev = c;
      i++;
      c = inputChars.at(i);
    }
  }
  str += c;
  if(c == '\n'){
    commentLineAdd++;
  }
  /*commentLen = str.length();
  if((str[commentLen - 1] == '#') && (str[commentLen - 2] == '|')){
    pushToken(COMMENT, str, lineCount);
    str = "";
    lineCount += commentLineAdd;
  }
  else{
    pushToken(UNDEFINED, str, lineCount);
    str = "";
    lineCount += commentLineAdd;
  }*/
  //pushComment(str, commentLineAdd);
};
void scanner::scanKeyWord(string &str){
  if(str == keywords[0]){
    pushToken(SCHEMES, str, lineCount);
    str = "";
  }
  else if(str == keywords[1]){
    pushToken(FACTS, str, lineCount);
    str = "";
  }
  else if(str == keywords[2]){
    pushToken(RULES, str, lineCount);
    str = "";
  }
  else if(str == keywords[3]){
    pushToken(QUERIES, str, lineCount);
    str = "";
  }
  else{
    ////cout << "Pushed " << str;
    if(!str.empty()){
    /*  bool hasLetter = false;
      int len = str.length();
      for(int i = 0; i < len; i++){
        if(isalpha(str[i])){
          hasLetter = true;
        }
      }
      if(hasLetter){
        pushToken(UNDEFINED,str,lineCount);
      }
      else{
        string charStr = "";
        for(int j = 0; j < len;j++){
          charStr = str[j];
          pushToken(UNDEFINED,charStr,lineCount);
        }
      }
      cout << "pushed :: " << str;*/
      undefinedNumCheck(str);
    }
    str = "";
  }
};
void scanner::undefinedNumCheck(string str){
  bool hasLetter = false;
  int len = str.length();
  for(int i = 0; i < len; i++){
    if(isalpha(str[i])){
      hasLetter = true;
    }
  }
  if(hasLetter){
    pushToken(UNDEFINED,str,lineCount);
  }
  else{
    string charStr = "";
    for(int j = 0; j < len;j++){
      charStr = str[j];
      pushToken(UNDEFINED,charStr,lineCount);
    }
  }
  //cout << "pushed :: " << str;
};
void scanner::scanID(string &str, int i, int length){
  if(i == (length - 1)){
    if(isalpha(str[0])){
      pushToken(ID, str, lineCount);
      str = "";
    }
  }
};
map <tokType, string> scanner::returnTokenMap(){
  return tokenMap;
};
