#pragma once
#include <cstdlib>
#include <vector>
#include "token.h"
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>

using namespace std;

class scanner{
private:
  string tokStr;
  string stringStr;
  string commentStr;
  string keywords[4];
  int keywordLen;
  int lineCount;
  int vecLength;
  token scannerToken;
  vector <token> tokens;
  vector <char> inputChars;
  map <tokType, string> tokenMap;
public:
  scanner();
  //void scanFile(string lineIn);
  void pushToken(tokType typeIn, string valIn, int lineIn);
  int pushCharToken(char valIn, int index);
  //int pushStringToken(char valIn, int index, int length);
  void scanFile(ifstream& fin);
  void loadMap();
  void printScanner();
  bool checkChars(char c,int &i);
  void keywordAndIDCheck(char c, int i);
  void stringCheck(char c, int &i, int length);
  void commentCheck(char c, int &i);
  bool checkIndex(int i, int length);
  void blockComment(string &str,char c, int length, int &i, int &commentLineAdd);
  void scanKeyWord(string &str);
  void scanID(string &str, int i, int length);
  void pushComment(string &str, int lineToAdd);
  void undefinedNumCheck(string str);
  vector <token> returnTokens();
  map <tokType, string> returnTokenMap();
};
