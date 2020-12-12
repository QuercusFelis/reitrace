// A. Groeling - 10/18/20
#ifndef MATERIAL_H
#define MATERIAL_H

#define ILLUM_NONMIRROR 2
#define ILLUM_MIRROR 3

#include <string>
#include "image.h"

struct Material
{
    std::string name = "";
    double ambient[3];
    double diffuse[3];
    double specular[3];
    double attenuation[3];
    double alpha = 16;
    double eta = 1;
    int illumModel = ILLUM_MIRROR;
    bool textured = false;
    Image texture = Image();
};

#endif
