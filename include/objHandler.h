//A. Groeling - 9/20/20
#ifndef objHandler_H
#define objHandler_H

#include "splitString.h"
#include "model.h"
#include <fstream>
#include <vector>

using namespace std;

// Constructs a model from a given obj file
static model modelConstruct(string &fileName)
{
    cout << "Opening " << fileName << "\n";
    //TODO: catch if file doesn't open
    ifstream file(fileName);
    model out;

    string header = "";
    vector<vector<double>> vertices;
    vector<line> lines;
    vector<face> faces;

    // parse file
    string newline;
    vector<string> tokens;
    while(getline(file, newline))
    {
        // split each line for easier parsing
        tokens.clear();
        splitString(newline, tokens);

        if(tokens.front().find("#") != string::npos)
        {
            header += newline + "\n";
        }
        // if it's a vertex
        else if(!tokens.front().compare("v"))
        {
            // and iterate through, converting tokens to doubles to build a vertex
            vector<double> vert;
            vert.push_back(stod(tokens.at(1)));
            vert.push_back(stod(tokens.at(2)));
            vert.push_back(stod(tokens.at(3)));
            vert.push_back((double)1);

            vertices.push_back(vert);
        }
        // if it's a face
        else if(!tokens.front().compare("f"))
        {
            // split the substrings to isolate integers
            vector<string> ftokens[3];
            for(int i = 0; i<3; i++)
            {
                splitString(tokens.at(i+1), ftokens[i], '/');
            }

            // fetch the data and pack into arrays
            int verts[3];// = {stoi(ftokens[0].at(0)), stoi(ftokens[1].at(0)), stoi(ftokens[2].at(0))};
            int texts[3];// = {0, 0, 0};
            int norms[3];// = {stoi(ftokens[0].at(2)), stoi(ftokens[1].at(2)), stoi(ftokens[2].at(2))};
            for(int i = 0; i<3; i++)
            {
                if(ftokens[i].at(0) != "")
                    verts[i] = std::stoi(ftokens[i].at(0));
                if(ftokens[i].at(1) != "")
                    texts[i] = std::stoi(ftokens[i].at(1));
                if(ftokens[i].at(2) != "")
                    norms[i] = std::stoi(ftokens[i].at(2));
            }
            
            //add to faces
            faces.push_back(face(verts, norms));
        }
        // if it's a line
        else if(!tokens.front().compare("l"))
        {
            // fetch line data and add to lines
            lines.push_back(line(stoi(tokens.at(1)), stoi(tokens.at(2))));
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
    for(vector<double> v : vertices)
    {
        verticesOut(0,i) = v.at(0);
        verticesOut(1,i) = v.at(1);
        verticesOut(2,i) = v.at(2);
        verticesOut(3,i) = v.at(3);

        i++;
    }

    // finish the model and return
    out.setHeader(header);
    out.setVertices(verticesOut);
    out.setFaces(faces);
    out.setLines(lines);
    
    return out;
}

//saves a model to a given location
static void modelDeconstruct(string &fileName, model &output)
{
    ofstream file(fileName);

    //retrieve data
    const MatrixXd vertices = output.getVertices();
    const vector<line> *lines = output.getLines();
    const vector<face> *faces = output.getFaces();

    //write to file, section by section
    file << *output.getHeader();
    for(int i = 0; i < vertices.cols(); i++)
    {
        file << "v "<< vertices(0,i) <<" "<< vertices(1,i) <<" "<< vertices(2,i) << "\n";
    }
    if(output.isSmooth())
        file << "s on\n";
    else
        file << "s off\n";
    for(line l:*lines)
    {
        file << "l " << l.vertices[0] << " " << l.vertices[1] << "\n";
    }
    for(face f:*faces)
    {
        file << "f ";
        for(int j = 0; j < 3; j++)
        {
            file << f.vertices[j] << "/"; 
            if(f.textures[j] != -1)
                file << f.textures[j];
            file << "/" << f.normals[j] << " ";
        }
        file << "\n";
    }

    //close file
    file.close();
}

#endif
