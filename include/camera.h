#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "linAlg.h"
#include "image.h"
#include "scene.h"
#include "ray.h"

class Camera
{
    private:
    Vector3d eye;
    Vector3d look;
    Vector3d up;

    Vector3d U;
    Vector3d V;
    Vector3d W;

    //clipping plane position in camera coord
    double nearPlane;
    struct {
        double left;
        double right;
        double top;
        double bottom;
    } bounds;

    struct RGB {
        double r;
        double g;
        double b;
    };

    public:
    Camera(){}

    Camera(double eX, double eY, double eZ,
           double lX, double lY, double lZ,
           double uX, double uY, double uZ,
           double a)
    {
        eye = Vector3d(eX, eY, eZ);
        look = Vector3d(lX, lY, lZ);
        up = Vector3d(uX, uY, uZ);

        W = (eye - look).normalized();
        U = up.cross(W).normalized();
        V = W.cross(U);

        nearPlane = a;
    }

    Image* renderImage(Image *image, Scene *scene)
    {
        double *r = image->getR();
        double *g = image->getG();
        double *b = image->getB();
        int width = image->getWidth();
        int height = image->getHeight();

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                static Ray ray = Ray();
                pixelInit(&ray, scene, j, i, width, height);
                static RGB rgb = calcLight(scene, &ray);

                r[i*height+j] = rgb.r;
                g[i*height+j] = rgb.g;
                b[i*height+j] = rgb.b;
            }
        }

        return image;
    }

    RGB calcLight(Scene *scene, Ray *ray)
    {
        static RGB rgb = {0.0, 0.0, 0.0};
        if(!ray->intersects())
            return rgb;

        Material *material = ray->getBestSphere()->getMaterial();
        rgb.r += material->ambient[0] * scene->ambientLight[0];
        rgb.g += material->ambient[1] * scene->ambientLight[1];
        rgb.b += material->ambient[2] * scene->ambientLight[2];
        Vector3d normal = (*ray->getBestPoint() - *ray->getBestSphere()->getCenterpoint()).normalized();
        for(Light lt:scene->lights)
        {
            static Vector3d toLt = lt.coords - ray->getBestPoint()->normalized();
            double NdotL = normal.dot(toLt);
            if(NdotL > 0)
            {
               rgb.r += material->diffuse[0] * lt.emittance[0] * NdotL;
               rgb.g += material->diffuse[1] * lt.emittance[1] * NdotL;
               rgb.b += material->diffuse[2] * lt.emittance[2] * NdotL;
                
               Vector3d toC = (*ray->getStart() - *ray->getBestPoint()).normalized();
               Vector3d spR = ((2 * NdotL * normal) - toLt).normalized();
               double CdotR = toC.dot(spR);
               if(CdotR > 0)
               {
                   rgb.r += material->specular[0] * lt.emittance[0] * pow(CdotR, material->alpha);
                   rgb.r += material->specular[1] * lt.emittance[1] * pow(CdotR, material->alpha);
                   rgb.r += material->specular[2] * lt.emittance[2] * pow(CdotR, material->alpha);
               }
            }
        }

        return rgb;
    }

    void pixelInit(Ray *ray, Scene *scene, int x, int y, int imgW, int imgH)
    {
        double pX = x/(imgW-1)*(bounds.right-bounds.left)+bounds.left;
        double pY= y/(imgH-1)*(bounds.bottom-bounds.top)+bounds.top;
        Vector3d start = eye + (nearPlane * W) + (pX * U) + (pY * V);
        Vector3d direction = start - eye;

        ray->setStart(start);
        ray->setDirection(direction);

        for(size_t i = 0; i < scene->spheres.size(); i++)
        {
            ray->sphereTest(&scene->spheres[i]);
        }
    }

    void setBounds(double left, double right, double bottom, double top)
    {
        bounds.left = left;
        bounds.right = right;
        bounds.bottom = bottom;
        bounds.top = top;
    }
};

#endif
