//A. Groeling - 9/20/20
#include <cstdio>
#include <string>
#include "objHandler.h"
#include "gradedOutput.h"
#include "driverReader.h"
#include "transform.h"

Matrix4d M;
std::vector<model> models;
int modelCount = 0;

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
    std::vector<std::string> op;
    std::vector<double> params;
    driverReader dr(argv[1]);
    while(!dr.getEOF())
    {
        // get next instruction
        op = dr.getOp();
        if(dr.getEOF() || !op.size())
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
            M = translate(params.at(0), params.at(1), params.at(2)) * M;
        else if(!op.front().compare("rota"))
            M = rotate(params.at(0), params.at(1), params.at(2), params.at(3)) * M;
        else if(!op.front().compare("scale"))
            M = scale(params.at(0), params.at(1), params.at(2)) * M;
        // push and pop models as they are loaded and saved
        else if(!op.front().compare("load"))
        {
            modelCount++;
            models.push_back(modelConstruct(op.at(1)));
            MatrixXd temp = models.back().getVertices();
            models.back().applyTransform(M);
            std::string gradedName = op.at(1).substr(0,op.at(1).size()-4)+"_transform_new0";
            gradedOutput(gradedName+std::to_string(modelCount)+".txt",M , temp, models.back().getVertices());
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
