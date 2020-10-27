//A. Groeling - 9/20/20
#ifndef MODEL_H
#define MODEL_H

#include "linAlg.h"
#include <iostream>
#include <vector>

class Line
{
  public:
    int vertices[2];

    Line(int vert0, int vert1)
    {
        vertices[0] = vert0;
        vertices[1] = vert1;
    }
};

class Face
{
  public:
    int vertices[3];
    int textures[3] = {-1,-1,-1};
    int normals[3];

    Face(int verts[3], int texts[3], int norms[3])
    {
        Face(verts, norms);
        for(int i = 0; i<3; i++)
            textures[i] = (int)texts[i];
    }

    Face(int verts[3], int norms[3])
    {
        for(int i = 0; i<3; i++)
        {
            vertices[i] = (int)verts[i];
            normals[i] = (int)norms[i];
        }
    }
};

class Model
{
  private:
    bool smooth;
    std::string header;
    MatrixXd vertices;
    std::vector<double> vertexNormals;
    std::vector<Line> lines;
    std::vector<Face> faces;

  public:
    Model(){}

    Model(MatrixXd verts, std::vector<double> vns, std::vector<Line> edges, std::vector<Face> sides, bool smoothShaded)
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

    void setLines(std::vector<Line> edges)
    {
        lines = edges;
    }

    void setFaces(std::vector<Face> sides)
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

    const std::vector<Line>* getLines()
    {
        return &lines;
    }

    const std::vector<Face>* getFaces()
    {
        return &faces;
    }

    bool isSmooth()
    {
        return smooth;
    }
};

#endif
