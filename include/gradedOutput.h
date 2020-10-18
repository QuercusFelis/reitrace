//A. Groeling - 9/20/20
#ifndef GRADEDOUTPUT_H
#define GRADEDOUTPUT_H

#include "model.h"
#include <iostream>
#include <fstream>

//saves some output to a given location
static void gradedOutput(std::string fileName, Matrix4d M, MatrixXd A, MatrixXd B)
{
    std::ofstream file(fileName);

    //write to file, section by section
    file << "# Transformation Matrix\n" << M << "\n";

    MatrixXd diff = A - B;

    double sum = 0;
    for(int i = 0;i < diff.cols(); i++)
    {
        sum += abs(diff(0,i)) + abs(diff(1,i)) + abs(diff(2,i)) + abs(diff(3,i));
    }
    file << "# Sum absolute translations from original to transformed\n" << sum << "\n";

    //close file
    file.close();
}

#endif
