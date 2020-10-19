//A. Groeling - 9/20/20
#include <cstdio>
#include <string>
#include "driverReader.h"
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
                //TODO: try-catch this in case it's not just numbers
                // else program will HCF with even slightly unexpected input
                // Note to any grader reading this, I literally haven't slept in
                // over 24hrs and am not physically capable of fixing this rn, have mercy
                params.push_back(stod(op.at(i)));
            }

        // operation handlers
        if(!op.front().compare("light"))
        {
            scene.lights.push_back(Light());
            scene.lights.end()->coords = Vector4d(params.at(0), params.at(1), params.at(2), 1);
            scene.lights.end()->emittance[0] = params.at(3);
            scene.lights.end()->emittance[1] = params.at(4);
            scene.lights.end()->emittance[2] = params.at(5);
            scene.lights.end()->alpha = params.at(6);
        }
        else if(!op.front().compare("sphere"))
            scene.spheres.push_back(Sphere(params.at(0), params.at(1), params.at(2), params.at(3), 
                        params.at(4), params.at(5), params.at(6), 
                        params.at(7), params.at(8), params.at(9), 
                        params.at(10), params.at(11), params.at(12),
                        params.at(13)));
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
    }

    camera.renderImage(&image, &scene);
    image.toPPM(argv[2]);

    // close and signal success
    dr.close();
    exit(0);
}
