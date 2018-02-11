#include "mesh.h"

Mesh::Mesh() : Tv(0.0f), Rv(0.0f), Sv(1.0f)
{

}
Mesh::Mesh(const Mesh &orig) : Tv(orig.Tv), Rv(orig.Rv), Sv(orig.Sv), verts(orig.verts), tris(orig.tris)
{

}

QVector<Mesh> Mesh::fromFile(QString filename)
{
    // TO-DO
    return QVector<Mesh>(0);
}
