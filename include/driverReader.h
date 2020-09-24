//A. Groeling - 9/20/20
#ifndef driverReader_H
#define driverReader_H

#include "splitString.h"
#include <fstream>
#include <vector>

using namespace std;

class driverReader
{
  private:
    bool eof;
    ifstream file;

  public:
    driverReader(string fileName)
    {
        file = ifstream(fileName);
        if(file.is_open()) eof = false;
    }

    driverReader(char *fileName)
    {
        file = ifstream(fileName);
        if(file.is_open()) eof = false;
    }

    ~driverReader()
    {
        file.close();
    }

    // retrieves the next operation listed in the driver
    vector<string> getOp()
    {
        vector<string> out;
        string op;

        // if there are more lines to retrieve, do so
        if(!eof && getline(file, op))
        {
            splitString(op, out);
            // trim off unecessary information
            if(!out.front().compare("trans"))
                out.erase(out.begin());
        }
        else eof = true;

        // returns null if you have reached the end
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
