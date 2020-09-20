//A. Groeling - 9/20/20
#ifndef objHandler_H
#define objHandler_H

#include "splitString.h"
#include "model.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

model
    ifstream file;

    driverReader(string fileName)
    {
        file = ifstream(fileName);
        if(file.is_open()) eof = false;
    }

    ~driverReader()
    {
        file.close();
    }

    vector<string> nextOp()

#endif
