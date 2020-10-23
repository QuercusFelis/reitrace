// A. Groeling - 10/19/20
#ifndef RAY_H
#define RAY_H

#include "linAlg.h"
#include "sphere.h"

class Ray
{
    private:
    Vector3d start;
    Vector3d direction;

    bool intersection;
    double bestTValue;
    Sphere *bestSphere;
    Vector3d bestPoint;

    public:
    Ray()
    {
        Ray(Vector3d(0,0,0), Vector3d(0,0,0));
    }

    Ray(Vector3d s, Vector3d d)
    {
        start = s;
        direction = d;
        intersection = false;
        bestTValue = INFINITY;
        bestSphere = NULL;
        bestPoint = Vector3d(0,0,0);
    }
    
    void sphereTest(Sphere *sphere)
    {
        Vector3d Tvect = (*sphere->getCenterpoint() - start);
        double v = Tvect.dot(direction);
        double cSquared = Tvect.dot(Tvect);
        double dSquared = pow(*sphere->getRadius(), 2) - (cSquared - pow(v,2));

        if(dSquared < 0)
        {
            double tValue = v - sqrt(dSquared);
            if(tValue < bestTValue && tValue > .0000001)
            {
                intersection = true;
                bestTValue = tValue;
                bestSphere = sphere;
                bestPoint = start + tValue * direction;
            }
        }
    }

    void reset()
    {
        bestTValue = INFINITY;
        intersection = false;
        bestSphere = NULL;
    }

    bool intersects()
    {
        return intersection;
    }

    Vector3d* getBestPoint()
    {
        if(intersects())
            return &bestPoint;
        return NULL;
    }

    Sphere* getBestSphere()
    {
        return bestSphere;
    }

    Vector3d* getStart()
    {
        return &start;
    }
    
    Vector3d* getDirection()
    {
        return &direction;
    }

    void setStart(Vector3d s)
    {
        start = s;
    }
    
    void setDirection(Vector3d d)
    {
        direction = d;
    }
};

#endif
