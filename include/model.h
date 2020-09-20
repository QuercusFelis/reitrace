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
    Matrix4Xf vertices;
    vector<line> lines;
    vector<face> faces;

  public:
    model();

    model(Matrix4Xf verts, vector<line> edges, vector<face> sides, bool smoothShaded)
    {
        vertices = verts;
        lines = edges;
        faces = sides;
        smooth = smoothShaded;
    }

    // apply a given 4x4 transfrom to the set of vertices
    void applyTransform(Matrix4f transform)
    {
        vertices = transform * vertices.transpose();
    }

    void setVertices(Matrix4Xf verts)
    {
        vertices = verts;
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

    const Matrix4Xf getVertices()
    {
        return vertices;
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
