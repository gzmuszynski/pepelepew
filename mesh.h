#ifndef MESH_H
#define MESH_H

#include "material.h"
#include "trianglefunction.h"

#include <QVector>

struct int4{
    int a, b, c;
    int m = 0;
};

class Mesh
{
public:
    QVector<Vertex> verts;
    QVector<int4> tris;

    float3 Tv;
    float3 Sv;
    float3 Rv;
    
    Mesh();
    Mesh(const Mesh &orig);

    static QPair<QVector<Mesh>, QVector<Material> > fromFile(QString filename);
};

#endif // MESH_H
