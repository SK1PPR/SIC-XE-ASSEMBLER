#pragma once

#include <map>
#include <string>

#include "structs.h"
#include "IO.h"

using namespace std;

const unsigned char FORMAT_1 = 1;
const unsigned char FORMAT_2 = 2;
const unsigned char FORMAT_3_4 = 3;

void deleteOpTab();
void deleteOpTab2();
void deleteOpTab3();
map<string, OpInfo *> *getOpTab();
