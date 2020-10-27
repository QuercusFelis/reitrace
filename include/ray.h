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

    double bestTValue;
    Sphere *bestSphere;
    Vector3d bestPoint;

    public:
    Ray()
    {
        start = Vector3d(0,0,0);
        direction = Vector3d(0,0,0);
        bestTValue = 999999999999;
        bestSphere = NULL;
        bestPoint = Vector3d(0,0,0);
    }
    
    double sphereTest(Sphere *sphere)
    {
        Vector3d Tvect = (*sphere->getCenterpoint() - start);
        double v = Tvect.dot(direction);
        double cSquared = Tvect.dot(Tvect);
        double dSquared = pow(*sphere->getRadius(), 2) - (cSquared - pow(v,2));

        if(dSquared > 0)
        {
            double tValue = v - sqrt(dSquared);
            if(tValue < bestTValue && tValue > 0.00001)
            {
                bestTValue = tValue;
                bestSphere = sphere;
                bestPoint = start + tValue * direction;
            }
        }

        return dSquared;
    }

    bool intersects()
    {
        return bestSphere != NULL;
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
