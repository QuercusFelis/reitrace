// A. Groeling - 10/18/20
#ifndef SPHERE_H
#define SPHERE_H

#include <string.h>
#include "linAlg.h"
#include "material.h"

class Sphere
{
    private: 
    Material material;
    Vector3d centerpoint;
    double radius;

    public:
    Sphere(double x, double y, double z, double r, Material m)
    {
        centerpoint = Vector3d(x, y, z);
        radius = r;
        material = m;
    }

    Vector3d getNormal(Vector3d point)
    {
        return (point - centerpoint).normalized();
    }

    Vector3d* getCenterpoint()
    {
        return &centerpoint;
    }

    double* getRadius()
    {
        return &radius;
    }

    Material *getMaterial()
    {
        return &material;
    }
};

#endif
