#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "light.h"
#include "sphere.h"
#include "model.h"

struct Scene
{
    int recursionDepth = 1;
    double ambientLight[3] = {0.5, 0.5, 0.5};
    std::vector<Light> lights;
    std::vector<Sphere> spheres;
    std::vector<Model> models;
    std::vector<Material> materials;
};

#endif
