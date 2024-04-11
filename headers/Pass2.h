#pragma once

#include "structs.h"
#include "IO.h"
#include "OpCodeGenerator.h"

void runPass2(ofstream *opFile, vector<cSect> *cSects, bool &successfullPass2);
