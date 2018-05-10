#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "token.h"
#include "tokType.h"
#include <unistd.h>
#include "parser.h"
#include "database.h"

using namespace std;

int main(int argc, char* argv[]){
  //string inFileStr = "/Users/michaelbriggs/Desktop/Winter 2018/CS236/project1/infiles/";
  //string myFileStr = "/Users/michaelbriggs/Desktop/Winter 2018/CS236/project1/myTestFiles/";
  //string inFileStr = "/home/michael/CS 236/lab5/testfiles/";
  string inFileStr = "";
  //tokType;
  scanner scanner;
  parser parser;
  database database;
  vector <token> tokenVec;
  map <tokType, string> tokenMap;
  datalogProgram datalogProgram;
  //cout << "Project1" << endl;
  //int count = 0;
  string line;
  //char c;
  if(argc > 0){ //setting file name variable
      inFileStr += argv[1];
      //myFileStr += argv[1];
  }
  //cout << inFileStr << endl;
  //cout << myFileStr << endl;
  ifstream fin(inFileStr.c_str()); //ifstream fin(myFileStr);
  if(!fin){
      cout << "Can't open file " << inFileStr << endl;
      //cout << "Can't open file " << myFileStr << endl;
      exit( -1 );
  }
  scanner.scanFile(fin);
//  scanner.printScanner();
  tokenVec = scanner.returnTokens();
  tokenMap = scanner.returnTokenMap();
  parser.parse(tokenVec, tokenMap);
  datalogProgram = parser.returnDatalogProgram();
  database.interpreter(datalogProgram);
  //parser.tokenInCheck();
  //cout << endl;
  fin.close();

  return 1;
}
