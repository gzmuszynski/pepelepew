#include "vertex.h"

Vertex::Vertex() :
    pos(0),
    normal(0),
    coord(0)
{

}

Vertex::Vertex(float x, float y, float z) :
    pos(x,y,z,1.0f),
    normal(0),
    coord(0)
{

}

Vertex::Vertex(const Vertex &v) :
    pos(v.pos),
    normal(v.normal),
    coord(v.coord)
{

}

Vertex::Vertex(float3 pos) :
    pos(pos,1.0f),
    normal(0),
    coord(0)
{

}

Vertex::Vertex(float3 pos, float3 normal, float3 coord) :
    pos(pos,1.0f),
    normal(normal),
    coord(coord)
{

}
