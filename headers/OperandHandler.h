#pragma once

#include <string>
#include <math.h>
#include "ExpressionEvaluator.h"
#include "StringUtilities.h"
#include <stdexcept>

using namespace std;
int valueOfLiteralOperand(string op);
int evaluateOperand(string operand, cSect *csect = NULL);
bool isValidOpNm(string operand);
int findExpressionType(string op);
int addressOfLiteralOperand(string op);
