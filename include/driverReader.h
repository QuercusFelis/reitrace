//A. Groeling - 9/20/20
#ifndef driverReader_H
#define driverReader_H

#include "splitString.h"
#include <fstream>
#include <vector>

class driverReader
{
  private:
    bool eof;
    std::ifstream file;

  public:
    driverReader(std::string fileName)
    {
        file = std::ifstream(fileName);
        if(file.is_open()) eof = false;
    }

    driverReader(char *fileName)
    {
        file = std::ifstream(fileName);
        if(file.is_open()) eof = false;
    }

    ~driverReader()
    {
        file.close();
    }

    // retrieves the next operation listed in the driver
    std::vector<std::string> getOp()
    {
        std::vector<std::string> out;
        std::string op;

        // if there are more lines to retrieve, do so
        if(getline(file, op))
        {
            if(op != "")
            {
                splitString(op, out);
                // trim off redundant "trans"
                if(!out.front().compare("trans"))
                    out.erase(out.begin());
                // ignore comments
                else if(out.front().find("#") != std::string::npos)
                    out = getOp();
            }
            else eof = true;
        }

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
