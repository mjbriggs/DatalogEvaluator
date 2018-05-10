#include <cstdlib>
#pragma once

using namespace std;

enum tokType{
  COMMA,
  PERIOD,
  Q_MARK,
  LEFT_PAREN,
  RIGHT_PAREN,
  COLON,
  COLON_DASH,
  MULTIPLY,
  ADD,
  SCHEMES,
  FACTS,
  RULES,
  QUERIES,
  ID,
  STRING,
  COMMENT,
  UNDEFINED,
  EoF
};
