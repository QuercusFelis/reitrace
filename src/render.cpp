//A. Groeling - 9/20/20
#include "include/render.h"
#include <cstdio>
#include <string>

Matrix4d M;
vector<model> models;

int main(int argc, char **argv)
{
    //check for valid input
    if(argc != 2)
    {
        fprintf(stderr, "Incorrect argument format (i.e. ./render driver00.txt");
        exit(1);
    }

    //initialize
    M.setIdentity();

    // parse driver file
    vector<string> op;
    vector<double> params;
    driverReader dr(argv[1]);
    while(!dr.getEOF())
    {
        // get next instruction
        op = dr.getOp();
        if(dr.getEOF())
            break;
        params.clear();

        // fill params with floats
        if(op.front().compare("load") != 0
          && op.front().compare("save") != 0)
            for(size_t i = 1; i < op.size(); i++)
            {
                params.push_back(stod(op.at(i)));
            }

        // operation handlers
        if(op.front().compare("clear"))
            M.setIdentity();
        else if(op.front().compare("move"))
            M = M * translate(params.at(0), params.at(1), params.at(2));
        else if(op.front().compare("rotate"))
            M = M * rotate(params.at(0), params.at(1), params.at(2), params.at(3));
        else if(op.front().compare("scale"))
            M = M * scale(params.at(0), params.at(1), params.at(2));
        // push and pop models as they are loaded and saved
        else if(op.front().compare("load"))
        {
            models.push_back(modelConstruct(op.at(1)));
            models.back().applyTransform(M);
        }
        else if(op.front().compare("save"))
        {
            modelDeconstruct(op.at(1), models.back());
            models.pop_back();
        }
    }

    // close and signal success
    dr.close();
    exit(0);
}
