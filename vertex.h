#ifndef VERTEX_H
#define VERTEX_H
#include <float4.h>


class Vertex
{
public:
    Vertex();
    Vertex(float x, float y, float z);
    Vertex(const Vertex &v);
    Vertex(float3 pos);
    Vertex(float3 pos, float3 normal, float3 coord);

    float4 pos;
    float3 normal;
    float3 coord;
};

#endif // VERTEX_H
