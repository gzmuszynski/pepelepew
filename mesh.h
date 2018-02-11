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

    float4 Tv;
    float4 Sv;
    float4 Rv;
    
    Mesh();
    Mesh(const Mesh &orig);

    static QVector<Mesh> fromFile(QString filename);
};

#endif // MESH_H
