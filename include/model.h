//A. Groeling - 9/20/20
#ifndef model_H
#define model_H

#include "linAlg.h"
#include <vector>

using namespace std;

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
    int textures[3];
    int normals[3];

    face(int verts[3], int texts[3], int norms[3])
    {
        face(verts, norms);
        for(int i = 0; i<3; i++)
            textures[i] = texts[i];
    }

    face(int verts[3], int norms[3])
    {
        for(int i = 0; i<3; i++)
        {
            vertices[i] = verts[i];
            normals[i] = norms[i];
        }
    }
};

class model
{
  private:
    bool smooth;
    MatrixXd vertices;
    vector<double> vertexNormals;
    vector<line> lines;
    vector<face> faces;

  public:
    model();

    model(MatrixXd verts, vector<double> vns, vector<line> edges, vector<face> sides, bool smoothShaded)
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
        vertices = transform * vertices.transpose();
    }

    void setVertices(MatrixXd verts)
    {
        vertices = verts;
    }

    void setVertexNormals(vector<double> vns)
    {
        vertexNormals = vns;
    }

    void setLines(vector<line> edges)
    {
        lines = edges;
    }

    void setFaces(vector<face> sides)
    {
        faces = sides;
    }

    void setSmooth(bool smoothShaded)
    {
        smooth = smoothShaded;
    }

    const MatrixXd getVertices()
    {
        return vertices;
    }

    const vector<double>* getVertexNormals()
    {
        return &vertexNormals;
    }

    const vector<line>* getLines()
    {
        return &lines;
    }

    const vector<face>* getFaces()
    {
        return &faces;
    }

    bool isSmooth()
    {
        return smooth;
    }
};

#endif
