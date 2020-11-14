// A. Groeling - 10/19/20
#ifndef RAY_H
#define RAY_H

#define SPHERE 1
#define MODEL 2

#include "linAlg.h"
#include "sphere.h"
#include "model.h"

class Ray
{
    private:
    Vector3d start;
    Vector3d direction;

    double bestTValue;
    void *bestObject;
    Vector3d bestPoint;
    Face *bestFace;
    int objType;

    public:
    Ray()
    {
        start = Vector3d(0,0,0);
        direction = Vector3d(0,0,0);
        bestTValue = INFINITY;
        bestObject = NULL;
        bestFace = NULL;
        bestPoint = Vector3d(0,0,0);
    }
    
    Ray(Vector3d L, Vector3d D)
    {
        start = L;
        direction = D;
        bestTValue = INFINITY;
        bestObject = NULL;
        bestFace = NULL;
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
                bestObject = sphere;
                bestPoint = start + tValue * direction;
                objType = SPHERE;
            }
        }

        return dSquared;
    }

    void modelTest(Model *m)
    {
        for(size_t i = 0; i < m->getFaces()->size(); i++)
            // if face intersects closer than the previous best
            if(faceTest(&m->getFaces()->at(i), m->getVertices()))
            {
                bestObject = m;
                objType = MODEL;
            }
    }

    bool faceTest(Face *f, MatrixXd *verts)
    {
        bool bestIntersect = false;
        // initialize triangle corners
        Vector3d A = f->getA(verts);
        Vector3d B = f->getB(verts);
        Vector3d C = f->getC(verts);
        // setup terms to solve for beta (X[0]), gamma (X[1]), and t (X[2])
        Vector3d X;
        Vector3d Y = A - start;
        Matrix3d M;
        for(int i = 0; i < 3; i++)
        {
            M(i,0) = A[i] - B[i];
            M(i,1) = A[i] - C[i];
            M(i,2) = direction[i];
        }
        // Calculate beta, gamma, and t
        X = M.inverse() * Y;
        //is point inside triange and in front of ray?
        if(X[0] >= 0 && X[1] >= 0 && X[2] > 0 && X[0] + X[1] <= 1)
            // is this intersection closer than the previous best?
            if(X[2] < bestTValue)
            {
                bestIntersect = true;
                bestTValue = X[2];
                bestPoint = start + X[2] * direction;
                bestFace = f;
            }

        return bestIntersect;
    }

    bool intersects()
    {
        return bestObject != NULL;
    }

    Vector3d* getBestPoint()
    {
        if(intersects())
            return &bestPoint;
        return NULL;
    }

    void* getBestObject()
    {
        return bestObject;
    }

    Face* getFace()
    {
        return bestFace;
    }

    int getObjType()
    {
        return objType;
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