//A. Groeling - 9/20/20
#ifndef model_H
#define model_H

#include "linAlg.h"
#include <iostream>
#include <vector>

class line
{
  public:
    int vertices[2];

    line(int vert0, int vert1)
    {
        vertices[0] = vert0;
        vertices[1] = vert1;
    }
};

class face
{
  public:
    int vertices[3];
    int textures[3] = {-1,-1,-1};
    int normals[3];

    face(int verts[3], int texts[3], int norms[3])
    {
        face(verts, norms);
        for(int i = 0; i<3; i++)
            textures[i] = (int)texts[i];
    }

    face(int verts[3], int norms[3])
    {
        for(int i = 0; i<3; i++)
        {
            vertices[i] = (int)verts[i];
            normals[i] = (int)norms[i];
        }
    }
};

class model
{
  private:
    bool smooth;
    std::string header;
    MatrixXd vertices;
    std::vector<double> vertexNormals;
    std::vector<line> lines;
    std::vector<face> faces;

  public:
    model(){}

    model(MatrixXd verts, std::vector<double> vns, std::vector<line> edges, std::vector<face> sides, bool smoothShaded)
    {
        vertices = verts;
        vertexNormals = vns;
        lines = edges;
        faces = sides;
        smooth = smoothShaded;
    }

    // apply a given 4x4 transfrom to the set of vertices
    void applyTransform(Matrix4d transform)
    {
        std::cout << "Applying Transform: \n" << transform << "\n\n";
        vertices = transform * vertices;
    }

    void setHeader(const std::string& head)
    {
        header = head;
    }

    void setVertices(MatrixXd verts)
    {
        vertices = verts;
    }

    void setVertexNormals(std::vector<double> vns)
    {
        vertexNormals = vns;
    }

    void setLines(std::vector<line> edges)
    {
        lines = edges;
    }

    void setFaces(std::vector<face> sides)
    {
        faces = sides;
    }

    void setSmooth(bool smoothShaded)
    {
        smooth = smoothShaded;
    }

    const std::string* getHeader()
    {
        return &header;
    }

    const MatrixXd getVertices()
    {
        return vertices;
    }

    const std::vector<double>* getVertexNormals()
    {
        return &vertexNormals;
    }

    const std::vector<line>* getLines()
    {
        return &lines;
    }

    const std::vector<face>* getFaces()
    {
        return &faces;
    }

    bool isSmooth()
    {
        return smooth;
    }
};

#endif
