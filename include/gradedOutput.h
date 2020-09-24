//A. Groeling - 9/20/20
#ifndef GRADEDOUTPUT_H
#define GRADEDOUTPUT_H

#include "model.h"
#include <fstream>

using namespace std;

//saves some output to a given location
static void gradedOutput(string fileName, Matrix4d M, MatrixXd A, MatrixXd B)
{
    ofstream file(fileName);

    //write to file, section by section
    file << "# Transformation Matrix\n" << M << "\n";

    MatrixXd diff = A - B;

    file << "# Sum absolute translations from original to transformed\n" << diff.sum() << "\n";

    //close file
    file.close();
}

#endif
