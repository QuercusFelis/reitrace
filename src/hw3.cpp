//A. Groeling - 9/20/20
#include <cstdio>
#include <string>
#include "driverReader.h"
#include "objHandler.h"
#include "transform.h"
#include "scene.h"
#include "camera.h"

int main(int argc, char **argv)
{
    //check for valid input
    if(argc != 3)
    {
        fprintf(stderr, "Incorrect argument format %i (i.e. ./render driver00.txt driver00.ppm)\n", argc);
        exit(1);
    }

    //initialize
    Matrix4d M;
    M.setIdentity();
    Scene scene;
    Camera camera;
    Image image;

    // parse driver file
    std::vector<std::string> op;
    std::vector<double> params;
    driverReader dr(argv[1]);
    while(!dr.getEOF())
    {
        // get next instruction
        op = dr.getOp();
        if(dr.getEOF() || !op.size())
            break;
        params.clear();
        
        // if not load/save, fill params
        if(op.front().compare("load")
          && op.front().compare("save"))
            for(size_t i = 1; i < op.size(); i++)
            {
                params.push_back(stod(op.at(i)));
            }

        // operation handlers
        if(!op.front().compare("light"))
        {
            Light light = { Vector3d(params.at(0), params.at(1), params.at(2)),
                    {params.at(4), params.at(5), params.at(6)}};
            scene.lights.push_back(light);
        }
        else if(!op.front().compare("sphere"))
        {
            Material m = { "sphere",
                {params.at(4), params.at(5), params.at(6)},
                {params.at(7), params.at(8), params.at(9)},
                {params.at(10), params.at(11), params.at(12)},
                {params.at(13), params.at(14), params.at(15)}, 
                16.0};
            scene.spheres.push_back(Sphere(params.at(0), params.at(1), params.at(2),
                        params.at(3), m));
        }
        else if(!op.front().compare("camera"))
            camera = Camera(params.at(0), params.at(1), params.at(2), 
                    params.at(3), params.at(4), params.at(5),
                    params.at(6), params.at(7), params.at(8),
                    params.at(9));
        else if(!op.front().compare("res"))
            image = Image(params.at(0), params.at(1));
        else if(!op.front().compare("bounds"))
            camera.setBounds(params.at(0), params.at(1), params.at(2), params.at(3));
        else if(!op.front().compare("ambient"))
        {
            scene.ambientLight[0] = params.at(0);
            scene.ambientLight[1] = params.at(1);
            scene.ambientLight[2] = params.at(2);
        }
        else if(!op.front().compare("recursionlevel"))
            scene.recursionDepth = params.at(0);
        // poly-model handling
        else if(!op.front().compare("clear"))
            M.setIdentity();
        else if(!op.front().compare("move"))
            M = translate(params.at(0), params.at(1), params.at(2)) * M;
        else if(!op.front().compare("rota"))
            M = rotate(params.at(0), params.at(1), params.at(2), params.at(3)) * M;
        else if(!op.front().compare("scale"))
            M = scale(params.at(0), params.at(1), params.at(2)) * M;
        // push and pop models as they are loaded and saved
        else if(!op.front().compare("load"))
        {
            scene.models.push_back(modelConstruct(op.at(1)));
            MatrixXd temp = *scene.models.back().getVertices();
            scene.models.back().applyTransform(M);
        }
        else if(!op.front().compare("save"))
        {
            modelDeconstruct(op.at(1), scene.models.back());
            scene.models.pop_back();
        }
 
    }

    // final output
    camera.renderImage(&image, &scene);
    image.toPPM(argv[2]);

    // close and signal success
    dr.close();
    exit(0);
}
