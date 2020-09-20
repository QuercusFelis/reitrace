//A. Groeling - 9/20/20
#ifndef driverReader_H
#define driverReader_H

#include "splitString.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class driverReader
{
    bool eof = true;
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
    {
        vector<string> out;
        string op;

        if(!eof && getline(file, op))
        {
            splitString(op, out);
            if(!out.front().compare("trans"))
                out.erase(out.begin());
        }
        else eof = true;

        return out;
    }

    bool getEOF()
    {
        return eof;
    }

    void close()
    {
        file.close();
    }
};

#endif
