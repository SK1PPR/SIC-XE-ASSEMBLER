#pragma once

#include "Parser.h"
#include "OpTab.h"
#include <string>
#include "StringUtilities.h"
#include "OperandHandler.h"
#include "ExpressionEvaluator.h"
using namespace std;

int validate(parsedLine pl);
bool isRubbish(string x);
bool isChar(char x);
bool isNumber(char a);
bool isReg(string o);
int f1(string o1, string o2);
int f2(string op, string o1, string o2);
int f34(string op, string o1, string o2);
void fillDirectives();
bool checkBYTE(string x);
bool checkLiteral(string x, bool isReg);
bool checkExt(string s);
