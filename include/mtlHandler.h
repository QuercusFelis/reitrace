//A. Groeling - 11/13/20
#ifndef mtlHandler_H
#define mtlHandler_H

#include "splitString.h"
#include "material.h"
#include <fstream>
#include <vector>

// Constructs a list of materials from a given mtl file
static std::vector<Material> materialConstruct(std::string &fileName)
{
    std::cout << "Opening " << fileName << "\n";
    //TODO: catch if file doesn't open
    std::ifstream file(fileName);
    std::vector<Material> out;

    // parse file
    std::string newline;
    std::vector<std::string> tokens;
    while(getline(file, newline))
    {
        // split each line for easier parsing
        tokens.clear();
        splitString(newline, tokens);
        
        if(tokens.size() != 0)
        {
            // if it's a new material
            if(!tokens.front().compare("newmtl"))
            {
                Material m;
                m.name = tokens.at(1);
                out.push_back(m);
            }
            // parse material properties
            else if(!tokens.front().compare("Ns"))
            {
                out.back().alpha = stod(tokens.at(1));
            }
            else if(!tokens.front().compare("Ka"))
            {
                for(int i = 1; i <= 3; i++)
                    out.back().ambient[i-1] = stod(tokens.at(i));
            }
            else if(!tokens.front().compare("Kd"))
            {
                for(int i = 1; i <= 3; i++)
                    out.back().diffuse[i-1] = stod(tokens.at(i));
            }
            else if(!tokens.front().compare("Ks"))
            {
                for(int i = 1; i <= 3; i++)
                    out.back().specular[i-1] = stod(tokens.at(i));
            }
            else if(!tokens.front().compare("Ke"))
            {
                for(int i = 1; i <= 3; i++)
                    out.back().attenuation[i-1] = stod(tokens.at(i));
            }
            else if(!tokens.front().compare("illum"))
            {
                out.back().illumModel = stoi(tokens.at(1));
            }
            else if(!tokens.front().compare("map_Kd"))
            {
                out.back().textured = true;
                std::cout << "Opening " << tokens.at(1) << "\n";
                //TODO: catch if file doesn't open
                std::ifstream imgFile(tokens.at(1));

                // parse file
                std::string imgNewline;
                std::vector<std::string> imgTokens;

                int x = 0;
                while(getline(imgFile, imgNewline))
                {
                    imgTokens.clear();
                    splitString(imgNewline, imgTokens);
                    if(imgTokens.size() == 0) break;
                    if(imgTokens.size() == 3)
                        out.back().texture = Image(stoi(imgTokens.at(0)), stoi(imgTokens.at(1)));
                    else if(imgTokens.back().compare("P3"))
                    {
                        Pixel p;
                        p.r = stod(imgTokens.at(0))/255;
                        getline(imgFile, imgNewline);
                        imgTokens.clear();
                        splitString(imgNewline, imgTokens);

                        p.g = stod(imgTokens.at(0))/255;
                        getline(imgFile, imgNewline);
                        imgTokens.clear();
                        splitString(imgNewline, imgTokens);

                        p.b = stod(imgTokens.at(0))/255;

                        out.back().texture.setPixel(x, 0, p);
                        x++;
                    }
                }
                imgFile.close();
                std::cout << "Closed " <<  tokens.at(1) << "\n";
            }
        }
    }
    file.close();
    std::cout << "Closed " << fileName << "\n";
    // done parsing file
    
    return out;
}

#endif
