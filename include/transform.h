//A. Groeling - 9/20/20
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "linAlg.h"
#include "lib/Eigen/Geometry"
#include <cmath>

// returns 4x4 identity matrix
static Matrix4d identity4f()
{
    Matrix4d out; 
    out.setIdentity();
    return out;
}

// returns 4x4 rotation matrix given axis-angle rotation
static Matrix4d rotate(double x, double y, double z, double theta)
{
    Matrix4d m;
    Vector3d axis(x, y, z);

    axis.normalize();
    // convert theta to radians
    theta = M_PI * theta/180;
   
    // make homogenous rotation matrix
    m.setIdentity();
    m.block<3,3>(0,0) = Eigen::AngleAxisd(theta, axis).toRotationMatrix();

    return m;
}

// returns 4x4 translation matrix
static Matrix4d translate(double x, double y, double z)
{
    Matrix4d m;
    m.setIdentity();
    m(0,3) = x;
    m(1,3) = y;
    m(2,3) = z;

    return m;
}

// returns 4x4 scaling matrix
static Matrix4d scale(double x, double y, double z)
{
    Matrix4d m;
    m << x, 0, 0, 0,
         0, y, 0, 0,
         0, 0, z, 0,
         0, 0, 0, 1;

    return m;
}

#endif
