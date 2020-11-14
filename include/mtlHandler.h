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
                out.back().ambient[i] = stod(tokens.at(i));
        }
        else if(!tokens.front().compare("Kd"))
        {
            for(int i = 1; i <= 3; i++)
                out.back().diffuse[i] = stod(tokens.at(i));
        }
        else if(!tokens.front().compare("Ks"))
        {
            for(int i = 1; i <= 3; i++)
                out.back().specular[i] = stod(tokens.at(i));
        }
        else if(!tokens.front().compare("Ke"))
        {
            for(int i = 1; i <= 3; i++)
                out.back().attenuation[i] = stod(tokens.at(i));
        }
        else if(!tokens.front().compare("illum"))
        {
            out.back().illumModel = stoi(tokens.at(1));
        }
    }
    file.close();
    // done parsing file
    
    return out;
}

#endif
