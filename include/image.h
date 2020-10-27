// A. Groeling - 10/19/20
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct Pixel{
    double r;
    double g;
    double b;
};

class Image
{
    private:
    // resolution
    int width;
    int height;

    // pixel value arrays
    std::vector<Pixel> pixels;

    public:
    Image(){}

    Image(int w, int h)
    {
        width = w;
        height = h;

        int numPixels = w * h;
        pixels = std::vector<Pixel>(numPixels);
    }

    bool toPPM(std::string fileName)
    {
        std::ofstream file(fileName);
        file << "P3\n";
        file << width << " " << height << " 255\n";
        
        // cap all values at 1
        for(int i = 0; i < width*height; i++)
        {
            if(pixels[i].r > 1)
                pixels[i].r = 1;
            if(pixels[i].g > 1)
                pixels[i].g = 1;
            if(pixels[i].b > 1)
                pixels[i].b = 1;
        }

        // write to file
        for(int i = 0; i < width*height; i++)
        {
            file << (int)(255*pixels[i].r) << " " 
                 << (int)(255*pixels[i].g) << " " 
                 << (int)(255*pixels[i].b) << " ";
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

    void setPixel(int x, int y, Pixel pixel)
    {
        pixels.at(y*width+x) = pixel;
    }
};

#endif
