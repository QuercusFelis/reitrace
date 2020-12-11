//A. Groeling - 9/20/20
#ifndef objHandler_H
#define objHandler_H

#include "splitString.h"
#include "model.h"
#include "mtlHandler.h"
#include <fstream>
#include <vector>

// Constructs a model from a given obj file
static Model modelConstruct(std::string &fileName)
{
    std::cout << "Opening " << fileName << "\n";
    //TODO: catch if file doesn't open
    std::ifstream file(fileName);
    Model out;

    std::string header = "";
    std::vector<std::vector<double>> vertices;
    std::vector<Face> faces;
    std::vector<std::vector<int>> vertexParents;
    Material *activeMaterial = NULL;

    // parse file
    std::string newline;
    std::vector<std::string> tokens;
    while(getline(file, newline))
    {
        // split each line for easier parsing
        tokens.clear();
        splitString(newline, tokens);

        if(tokens.front().find("#") != std::string::npos)
        {
            header += newline + "\n";
        }
        else if(!tokens.front().compare("mtllib"))
        {
            out.setMaterials(materialConstruct(tokens.at(1)));
        }
        // if it's a vertex
        else if(!tokens.front().compare("v"))
        {
            // and iterate through, converting tokens to doubles to build a vertex
            std::vector<double> vert;
            vert.push_back(stod(tokens.at(1)));
            vert.push_back(stod(tokens.at(2)));
            vert.push_back(stod(tokens.at(3)));
            vert.push_back((double)1);

            vertexParents.push_back(std::vector<int>());
            vertices.push_back(vert);
        }
        // set activeMaterial pointer
        else if(!tokens.front().compare("usemtl"))
        {
            activeMaterial = out.getMaterial(tokens.at(1));
        }
        // if it's a face
        else if(!tokens.front().compare("f"))
        {
            // split the substrings to isolate integers
            std::vector<std::string> ftokens[3];
            int verts[3];
            int texts[3] = {0, 0, 0};

            // determine how face is defined in .obj
            std::string format = "//";
            if(tokens.at(1).find('/') == std::string::npos)
                format = "";
            else if(tokens.at(1).find('/') == tokens.at(1).rfind('/'))
                format = "/";

            // splitstring each parameter for easier handling
            for(int i = 0; i<3; i++)
            {
                if(format.compare(""))
                    splitString(tokens.at(i+1), ftokens[i], '/');
                else
                    ftokens[i] = std::vector<std::string>({tokens[i+1]});
            }

            // conditionally pack into arrays
            for(int i = 0; i<3; i++)
            {
                verts[i] = std::stoi(ftokens[i].at(0));
                vertexParents.at(verts[i]-1).push_back(faces.size());
                if(!format.compare("/") || ftokens[i].at(0).size() == 3)
                    texts[i] = std::stoi(ftokens[i].at(1));
            }
            
            //add to faces
            faces.push_back(Face(activeMaterial, verts));
        }
        // if it has smoothing defined
        else if(!tokens.front().compare("s"))
        {
            if(!tokens.at(1).compare("off"))
                out.setSmooth(false);
            else
                out.setSmooth(true);
        }
    }
    file.close();
    // done parsing file

    // initialize dynamic matrix to known size and fill
    MatrixXd verticesOut(4,(int)vertices.size());
    int i = 0;
    for(std::vector<double> v : vertices)
    {
        verticesOut(0,i) = v.at(0);
        verticesOut(1,i) = v.at(1);
        verticesOut(2,i) = v.at(2);
        verticesOut(3,i) = v.at(3);

        i++;
    }

    Material m; 
    // finish the model and return
    out.setHeader(header);
    out.setVertices(verticesOut);
    out.setFaces(faces);
    out.setVertexParents(vertexParents);
    
    return out;
}

#endif
