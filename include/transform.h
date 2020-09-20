//A. Groeling - 9/20/20
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "linAlg.h"
#include "Eigen/Geometry"
#include <cmath>

Matrix4f identity4f()
{
    Matrix4f out = Matrix4f::Zero(); 
    out.setIdentity();
    return out;
}

void identity4f(Matrix4f &in)
{
    in.setIdentity();
}

Matrix4f rotate(float x, float y, float z, float theta)
{
    Matrix4f m;
    Vector3f axis(x, y, z);

    axis.normalize();
    // convert theta to radians
    theta = M_PI * theta/180;
   
    // make homogenous rotation matrix
    m.setIdentity();
    m.block<3,3>(0,0) = (Matrix4f)Eigen::AngleAxisf(theta, axis);

    return m;
}

Matrix4f translate(float x, float y, float z)
{
    Matrix4f m;
    m.setIdentity();
    m(0,3) = x;
    m(1,3) = y;
    m(2,3) = z;

    return m;
}

Matrix4f scale(float x, float y, float z)
{
    Matrix4f m;
    m << x, 0, 0, 0,
         0, y, 0, 0,
         0, 0, z, 0,
         0, 0, 0, 1;

    return m;
}
#endif
