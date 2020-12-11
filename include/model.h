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
    Material *material;
    int vertices[3];
    int textures[3] = {-1,-1,-1};
    Vector3d normal = {0,0,0};

  public:
    Face(Material *m, int verts[3], int texts[3])
    {
        Face(m, verts);
        for(int i = 0; i<3; i++)
            textures[i] = (int)texts[i]-1;
    }

    Face(Material *m, int verts[3])
    {
        material = m;
        for(int i = 0; i<3; i++)
        {
            vertices[i] = (int)verts[i]-1;
        }
    }

    void setMaterial(Material *m)
    {
        material = m;
    }

    void setNormal(Vector3d *norm)
    {
        normal = *norm;
    }

    Material* getMaterial()
    {
        return material;
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
    
    Vector3d getNormal()
    {
        return normal;
    }

    int getVertIndex(int i)
    {
        return vertices[i]+1;
    }

    int getTextureIndex(int i)
    {
        return textures[i]+1;
    }
};

class Model
{
  private:
    bool smooth;
    std::vector<Material> materials;
    std::string header;
    MatrixXd vertices;
    std::vector<Vector3d> vertexNormals;
    std::vector<Face> faces;
    std::vector<std::vector<int>> vertexParents;

  public:
    Model(){}

    Model(MatrixXd verts, std::vector<Vector3d> vns, std::vector<Face> sides, bool smoothShaded)
    {
        vertices = verts;
        vertexNormals = vns;
        faces = sides;
        smooth = smoothShaded;
    }

    // apply a given 4x4 transfrom to the set of vertices
    void applyTransform(Matrix4d transform)
    {
        std::cout << "Applying Transform: \n" << transform << "\n\n";
        vertices = transform * vertices;
    }

    Vector3d getNormal(Face *f)
    {
        Vector3d normal = f->getNormal();
        if(normal.dot(normal) == 0)
        {
            normal = (f->getA(&vertices) - f->getB(&vertices)).cross(f->getA(&vertices) - f->getC(&vertices)).normalized();
            f->setNormal(&normal);
        }
        return normal;
    }

    Vector3d getNormal(Face *f, double beta, double gamma)
    {
            if(!smooth) 
                return getNormal(f);
            else
                return (1-beta-gamma) * vertexNormals.at(f->getVertIndex(0)-1) + 
                        beta * vertexNormals.at(f->getVertIndex(1)-1) +
                        gamma * vertexNormals.at(f->getVertIndex(2)-1);
    }

    Material* getMaterial(std::string name)
    {
        Material *out = NULL;
        for(size_t i = 0; i < materials.size(); i++)
        {
            if(!materials.at(i).name.compare(name))
            {
                out = &materials.at(i);
            }
        }

        return out;
    }

    void setMaterials(std::vector<Material> m)
    {
        materials = m;
    }

    void setHeader(const std::string& head)
    {
        header = head;
    }

    void setVertices(MatrixXd verts)
    {
        vertices = verts;
    }

    void setVertexNormals()
    {
        for(size_t i = 0; i < vertexParents.size(); i++)
        {
            Vector3d normal;
            for(size_t j = 0; j < vertexParents.at(i).size(); j++)
            {
                normal += getNormal(&faces.at(vertexParents.at(i).at(j)));
            }
            normal /= vertexParents.at(i).size();
            vertexNormals.push_back(normal);
        }
    }

    void setVertexParents(std::vector<std::vector<int>> vps)
    {
        vertexParents = vps;
    }

    void setFaces(std::vector<Face> sides)
    {
        faces = sides;
    }

    void setSmooth(bool smoothShaded)
    {
        smooth = smoothShaded;
    }

    std::string* getHeader()
    {
        return &header;
    }

    MatrixXd* getVertices()
    {
        return &vertices;
    }

    std::vector<Vector3d>* getVertexNormals()
    {
        return &vertexNormals;
    }

    std::vector<std::vector<int>>* getVertexParents()
    {
        return &vertexParents;
    }

    std::vector<Face>* getFaces()
    {
        return &faces;
    }

    bool isSmooth()
    {
        return smooth;
    }
};

#endif
