//A. Groeling - 9/20/20
#ifndef MODEL_H
#define MODEL_H

#include "linAlg.h"
#include "material.h"
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
  private:
    int vertices[3];
    int textures[3] = {-1,-1,-1};
    int normals[3];

  public:
    Face(int verts[3], int texts[3], int norms[3])
    {
        Face(verts, norms);
        for(int i = 0; i<3; i++)
            textures[i] = (int)texts[i]-1;
    }

    Face(int verts[3], int norms[3])
    {
        for(int i = 0; i<3; i++)
        {
            vertices[i] = (int)verts[i]-1;
            normals[i] = (int)norms[i]-1;
        }
    }

    Vector3d getA(MatrixXd *verts)
    {
        Vector3d A = Vector3d(verts->operator()(0,vertices[0])/verts->operator()(3,vertices[0]),
                              verts->operator()(1,vertices[0])/verts->operator()(3,vertices[0]),
                              verts->operator()(2,vertices[0])/verts->operator()(3,vertices[0]));
        return A;
    }
    
    Vector3d getB(MatrixXd *verts)
    {
        Vector3d B = Vector3d(verts->operator()(0,vertices[1])/verts->operator()(3,vertices[1]),
                              verts->operator()(1,vertices[1])/verts->operator()(3,vertices[1]),
                              verts->operator()(2,vertices[1])/verts->operator()(3,vertices[1]));
        return B;
    }

    Vector3d getC(MatrixXd *verts)
    {
        Vector3d C = Vector3d(verts->operator()(0,vertices[2])/verts->operator()(3,vertices[2]),
                              verts->operator()(1,vertices[2])/verts->operator()(3,vertices[2]),
                              verts->operator()(2,vertices[2])/verts->operator()(3,vertices[2]));
        return C;
    }

    int getVertIndex(int i)
    {
        return vertices[i]+1;
    }

    int getTextureIndex(int i)
    {
        return textures[i]+1;
    }

    int getNormalIndex(int i)
    {
        return normals[i]+1;
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
    Material material;

  public:
    Model(){}

    Model(MatrixXd verts, std::vector<double> vns, std::vector<Line> edges, std::vector<Face> sides, bool smoothShaded, Material m)
    {
        vertices = verts;
        vertexNormals = vns;
        lines = edges;
        faces = sides;
        smooth = smoothShaded;
        material = m;
    }

    // apply a given 4x4 transfrom to the set of vertices
    void applyTransform(Matrix4d transform)
    {
        std::cout << "Applying Transform: \n" << transform << "\n\n";
        vertices = transform * vertices;
    }

    Vector3d getNormal(Face *f)
    {
        return (f->getA(&vertices) - f->getB(&vertices)).cross(f->getA(&vertices) - f->getC(&vertices));
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

    void setMaterial(Material m)
    {
        material = m;
    }

    std::string* getHeader()
    {
        return &header;
    }

    MatrixXd* getVertices()
    {
        return &vertices;
    }

    std::vector<double>* getVertexNormals()
    {
        return &vertexNormals;
    }

    std::vector<Line>* getLines()
    {
        return &lines;
    }

    std::vector<Face>* getFaces()
    {
        return &faces;
    }

    Material getMaterial()
    {
        return material;
    }

    bool isSmooth()
    {
        return smooth;
    }
};

#endif
