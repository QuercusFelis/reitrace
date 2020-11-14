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
        int width = image->getWidth();
        int height = image->getHeight();

        for(int x = 0; x < width; x++)
        {
            for(int y = 0; y < height; y++)
            {
                Pixel pixel = {0.0,0.0,0.0};
                Ray ray = Ray();
                pixelInit(&ray, scene, x, y, width, height);
                pixel = calcLight(scene, &ray, scene->recursionDepth);

                image->setPixel(x, y, pixel);
            }
        }

        return image;
    }

    Pixel calcLight(Scene *scene, Ray *ray, int level, 
            double rAttenuate = 1, double gAttenuate = 1, double bAttenuate = 1)
    {
        Pixel rgb = {0.0, 0.0, 0.0};

        if(!ray->intersects())
            return rgb;

        int objType = ray->getObjType();
        void *object = ray->getBestObject();
        Material *material;
        Vector3d normal;
        if(objType == SPHERE)
        {
            material = ((Sphere *)object)->getMaterial();
            normal = ((Sphere *)object)->getNormal(*ray->getBestPoint());
        }
        if(objType == MODEL)
        {
            material = ray->getFace()->getMaterial();
            normal = ((Model *)object)->getNormal(ray->getFace());
            if(normal.dot(*ray->getDirection()) > 0)
                normal = -1 * normal;
        }
        rgb.r += material->ambient[0] * scene->ambientLight[0];
        rgb.g += material->ambient[1] * scene->ambientLight[1];
        rgb.b += material->ambient[2] * scene->ambientLight[2];
        for(size_t i = 0; i < scene->lights.size(); i++)
        {
            bool lightOccluded = false;
            Light lt = scene->lights.at(i);
            Vector3d toLt = (lt.coords - *ray->getBestPoint()).normalized();
            double NdotL = normal.dot(toLt);
            // shadow detection
            Ray shadowDetect((*ray->getBestPoint() + toLt * 0.00001), toLt);
            raySceneTest(&shadowDetect, scene);
            if(shadowDetect.intersects())
                lightOccluded = (lt.coords - *ray->getBestPoint()).dot(lt.coords - *ray->getBestPoint()) > (*shadowDetect.getBestPoint() - *ray->getBestPoint()).dot(*shadowDetect.getBestPoint() - *ray->getBestPoint());
            if(NdotL > 0 && !lightOccluded)
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
                   rgb.g += material->specular[1] * lt.emittance[1] * pow(CdotR, material->alpha);
                   rgb.b += material->specular[2] * lt.emittance[2] * pow(CdotR, material->alpha);
               }
            }
        }
        if(level > 0) // recursive reflections
        {
            Pixel rgbR;
            Vector3d Uinv = -1 * *ray->getDirection();
            Ray reflectionRay(*ray->getBestPoint(), ((2 * normal.dot(Uinv) * normal) - Uinv).normalized());
            raySceneTest(&reflectionRay, scene);
            if(material->illumModel == 2)
                rgbR = calcLight(scene, &reflectionRay, level-1, 
                        material->attenuation[0], material->attenuation[1], material->attenuation[2]);
            else // illumModel must = 3, therefore Kr = Ks
                rgbR = calcLight(scene, &reflectionRay, level-1, 
                        material->specular[0], material->specular[1], material->specular[2]);
            rgb.r += rgbR.r * rAttenuate;
            rgb.g += rgbR.g * gAttenuate;
            rgb.b += rgbR.b * bAttenuate;
        }

        return rgb;
    }

    void pixelInit(Ray *ray, Scene *scene, int x, int y, int imgW, int imgH)
    {
        double pX = ((double)x)/(imgW-1)*(bounds.right-bounds.left)+bounds.left;
        double pY = ((double)y)/(imgH-1)*(bounds.bottom-bounds.top)+bounds.top;
        Vector3d start = eye + (nearPlane * W) + (pX * U) + (pY * V);
        Vector3d direction = (start - eye).normalized();

        ray->setStart(start);
        ray->setDirection(direction);
        raySceneTest(ray, scene);
    }

    void raySceneTest(Ray *ray, Scene *scene)
    {
        for(size_t i = 0; i < scene->spheres.size(); i++)
        {
            ray->sphereTest(&scene->spheres[i]);
        }
        for(size_t i = 0; i < scene->models.size(); i++)
        {
            ray->modelTest(&scene->models[i]);
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
