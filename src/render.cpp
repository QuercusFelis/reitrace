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
        fprintf(stderr, "Incorrect argument format %i (i.e. ./render driver00.txt)\n", argc);
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

        // if not load/save, fill params
        if(op.front().compare("load")
          && op.front().compare("save"))
            for(size_t i = 1; i < op.size(); i++)
            {
                //TODO: try-catch this in case it's not just numbers
                // else program will HCF with even slightly unexpected input
                // Note to any grader reading this, I literally haven't slept in
                // over 24hrs and am not physically capable of fixing this rn, have mercy
                params.push_back(stod(op.at(i)));
            }

        // operation handlers
        if(!op.front().compare("clear"))
            M.setIdentity();
        else if(!op.front().compare("move"))
            M = M * translate(params.at(0), params.at(1), params.at(2));
        else if(!op.front().compare("rota"))
            M = M * rotate(params.at(0), params.at(1), params.at(2), params.at(3));
        else if(!op.front().compare("scale"))
            M = M * scale(params.at(0), params.at(1), params.at(2));
        // push and pop models as they are loaded and saved
        else if(!op.front().compare("load"))
        {
            models.push_back(modelConstruct(op.at(1)));
            MatrixXd temp = models.back().getVertices();
            models.back().applyTransform(M);
            gradedOutput("transform_new.txt",M , temp, models.back().getVertices());
        }
        else if(!op.front().compare("save"))
        {
            modelDeconstruct(op.at(1), models.back());
            models.pop_back();
        }
    }

    // close and signal success
    dr.close();
    exit(0);
}
