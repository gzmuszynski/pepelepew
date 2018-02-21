#ifndef MESH_H
#define MESH_H

#include "trianglefunction.h"

#include <QVector>

struct int3{
    int a, b, c;
};

class Mesh
{
public:
    QVector<Vertex> verts;
    QVector<int3> tris;

    float3 Tv;
    float3 Sv;
    float3 Rv;
    
    Mesh();
    Mesh(const Mesh &orig);

    static QVector<Mesh> fromFile(QString filename);
};

#endif // MESH_H
