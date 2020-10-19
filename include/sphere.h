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
    Vector4d centerpoint;
    double radius;

    public:
    Sphere(double x, double y, double z, double r, 
            double aR, double aG, double aB, 
            double dR, double dG, double dB, 
            double sR, double sG, double sB,
            double alpha)
    {
        Material m;
        double a[3] = {aR, aG, aB};
        double d[3] = {dR, dG, dB};
        double s[3] = {sR, sG, sB};
        memcpy(m.ambient, a, sizeof(double [3]));
        memcpy(m.diffuse, d, sizeof(double [3]));
        memcpy(m.specular, s, sizeof(double [3]));
        m.alpha = alpha;

        Sphere(x, y, z, r, m);
    }

    Sphere(double x, double y, double z, double r, Material m)
    {
        centerpoint = Vector4d(x, y, z, 1);
        radius = r;
        material = m;
    }

    Vector4d* getCenterpoint()
    {
        return &centerpoint;
    }

    double* getRadius()
    {
        return &radius;
    }

    Material* getMaterial()
    {
        return &material;
    }
};

#endif
