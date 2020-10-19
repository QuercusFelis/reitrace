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
    Vector4d eye;
    Vector4d look;
    Vector4d up;

    Vector4d U;
    Vector4d V;
    Vector4d W;

    //clipping plane position in camera coord
    double nearPlane;
    struct {
        double left;
        double right;
        double top;
        double bottom;
    } bounds;

    public:
    Camera(){}

    Camera(double eX, double eY, double eZ,
           double lX, double lY, double lZ,
           double uX, double uY, double uZ,
           double a)
    {
        eye = Vector4d(eX, eY, eZ, 1);
        look = Vector4d(lX, lY, lZ, 1);
        up = Vector4d(uX, uY, uZ, 1);

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

        double *rgb;
        Ray ray;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                pixelInit(&ray, scene, j, i, width, height);
                rgb = calcLight(scene, &ray);

                r[i*height+j] = rgb[0];
                g[i*height+j] = rgb[1];
                b[i*height+j] = rgb[2];

                ray.reset();
            }
        }

        return image;
    }

    double* calcLight(Scene *scene, Ray *ray)
    {
        static double rgb[] = {0.0, 0.0, 0.0};
        if(!ray->intersects())
            return rgb;

        Material *material = ray->getBestSphere()->getMaterial();
        for(int i = 0; i < 3; i++)
        {
            rgb[i] += material->ambient[i] * scene->ambientLight[i];
        }
        Vector4d normal = (*ray->getBestPoint() - *ray->getBestSphere()->getCenterpoint()).normalized();
        for(Light lt:scene->lights)
        {
            static Vector4d toLt = lt.coords - ray->getBestPoint()->normalized();
            double NdotL = normal.dot(toLt);
            if(NdotL > 0)
            {
               for(int i = 0; i < 3; i++)
               {
                   rgb[i] += material->diffuse[i] * lt.emittance[i] * NdotL;
               }
                
               Vector4d toC = (*ray->getStart() - *ray->getBestPoint()).normalized();
               Vector4d spR = ((2 * NdotL * normal) - toLt).normalized();
               double CdotR = toC.dot(spR);
               if(CdotR > 0)
                for(int i = 0; i < 3; i++)
                {
                       rgb[i] += material->specular[i] * lt.emittance[i] * pow(CdotR, material->alpha);
                };
            }
        }

        return rgb;
    }

    void pixelInit(Ray *ray, Scene *scene, int x, int y, int imgW, int imgH)
    {
        double pX = x/(imgW-1)*(bounds.right-bounds.left)+bounds.left;
        double pY= y/(imgH-1)*(bounds.bottom-bounds.top)+bounds.top;
        Vector4d start = eye + (nearPlane * W) + (pX * U) + (pY * V);
        Vector4d direction = start - eye;

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
