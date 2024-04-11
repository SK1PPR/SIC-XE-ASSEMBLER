#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include "structs.h"
#include "StringUtilities.h"
#include <stdexcept>

using namespace std;

bool validateExpression(string exp);
bool isRelativeExpression(string exp);
int evaluateExpression(string exp, cSect *cs, bool useDummyValues = false);
