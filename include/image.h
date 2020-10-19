// A. Groeling - 10/19/20
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <fstream>

class Image
{
    private:
    // resolution
    int width;
    int height;

    // pixel value arrays
    double *r;
    double *g;
    double *b;

    public:
    Image(){}

    Image(int w, int h)
    {
        width = w;
        height = h;

        int pixels = w * h;

        r = new double[pixels];
        g = new double[pixels];
        b = new double[pixels];
    }

    ~Image()
    {
        delete[]r;
        delete[]g;
        delete[]b;
    }

    bool toPPM(std::string fileName)
    {
        std::ofstream file(fileName);
        file << "P3\n";
        file << width << " " << height << " 255\n";
        
        // cap all values at 1
        for(int i = 0; i < width*height; i++)
        {
            if(r[i] > 1)
                r[i] = 1;
            if(g[i] > 1)
                g[i] = 1;
            if(b[i] > 1)
                b[i] = 1;
        }

        // write to file
        for(int i = 0; i < width*height; i++)
        {
            file << (int)(255*r[i]) << " " << (int)(255*g[i]) << " " << (int)(255*b[i]) << " ";
            if(!width%(i+1))
                file << "\n";
        }
        return true;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    double* getR()
    {
        return r;
    }

    double* getG()
    {
        return g;
    }

    double* getB()
    {
        return b;
    }
};

#endif
