//A. Groeling - 9/20/20
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "linAlg.h"
#include "Eigen/Geometry"
#include <cmath>

// returns 4x4 identity matrix
static Matrix4f identity4f()
{
    Matrix4f out; 
    out.setIdentity();
    return out;
}

// returns 4x4 rotation matrix given axis-angle rotation
static Matrix4f rotate(float x, float y, float z, float theta)
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

// returns 4x4 translation matrix
static Matrix4f translate(float x, float y, float z)
{
    Matrix4f m;
    m.setIdentity();
    m(0,3) = x;
    m(1,3) = y;
    m(2,3) = z;

    return m;
}

// returns 4x4 scaling matrix
static Matrix4f scale(float x, float y, float z)
{
    Matrix4f m;
    m << x, 0, 0, 0,
         0, y, 0, 0,
         0, 0, z, 0,
         0, 0, 0, 1;

    return m;
}

#endif
