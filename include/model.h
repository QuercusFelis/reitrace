//A. Groeling - 9/20/20
#ifndef model_H
#define model_H

#include "Eigen/Core"
#include "linAlg.h"
#include <vector>

using namespace std;

class model
{
    Matrix4Xf vertices;

    model(Matrix4Xf verts)
    {
        vertices = verts;
    }

    void applyTransform(Matrix4f transform)
    {
        vertices = transform * vertices.transpose();
    }
};

#endif
