// A. Groeling - 10/19/20
#ifndef RAY_H
#define RAY_H

#include "linAlg.h"
#include "sphere.h"

class Ray
{
    private:
    Vector4d start;
    Vector4d direction;

    double bestTValue = INFINITY;
    Sphere *bestSphere;
    Vector4d bestPoint;

    public:
    Ray(){}

    Ray(Vector4d s, Vector4d d)
    {
        start = s;
        direction = d;
    }
    
    bool sphereTest(Sphere *sphere)
    {
        bool intersects = false;
        Vector4d Tvect = (*sphere->getCenterpoint() - start);
        double v = Tvect.dot(direction);
        double cSquared = Tvect.dot(Tvect);
        double dSquared = pow(*sphere->getRadius(), 2) - (cSquared - pow(v,2));

        if(dSquared < 0)
        {
            double tValue = v - sqrt(dSquared);
            if(tValue < bestTValue && tValue > .0000001)
            {
                bestTValue = tValue;
                bestSphere = sphere;
                bestPoint = start + tValue * direction;
            }
        }
        return intersects;
    }

    void reset()
    {
        bestTValue = INFINITY;
        bestSphere = NULL;
    }

    bool intersects()
    {
        return bestSphere != NULL;
    }

    Vector4d* getBestPoint()
    {
        if(intersects())
            return &bestPoint;
        return NULL;
    }

    Sphere* getBestSphere()
    {
        return bestSphere;
    }

    Vector4d* getStart()
    {
        return &start;
    }
    
    Vector4d* getDirection()
    {
        return &direction;
    }

    void setStart(Vector4d s)
    {
        start = s;
    }
    
    void setDirection(Vector4d d)
    {
        direction = d;
    }
};

#endif
