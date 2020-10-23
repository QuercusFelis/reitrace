// A. Groeling - 10/18/20
#ifndef LIGHT_H
#define LIGHT_H

#include "linAlg.h"

struct Light
{
    Vector3d coords;
    double emittance[3];
    double alpha;
};

#endif
