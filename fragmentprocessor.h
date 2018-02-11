#ifndef FRAGMENTPROCESSOR_H
#define FRAGMENTPROCESSOR_H

#include "buffer.h"
#include "vertexprocessor.h"

class FragmentShader;

class FragmentProcessor
{
public:
    FragmentProcessor();

    VertexProcessor* vp;
    FragmentShader* fragmentShader;
    TriangleFunction tf;

    void rasterize(Buffer &buffer);

    float4 minmax(Vertex* &triangle);

    QVector<int3> triangleBuffer;
    float4 triangleBounds(Vertex *&triangle);
};

class Fragment
{
public:
    Fragment(float4 color, float4 depth, float4 normal, float4 position) :
        color(color),
        depth(depth),
        normal(normal),
        position(position) {}

    float4 color;
    float4 depth;
    float4 normal;
    float4 position;
};

class FragmentShader
{
public:
    FragmentShader(FragmentProcessor* fp);

    virtual Fragment process(Vertex* &triangle, Hit &hit);

protected:
    FragmentProcessor* fp;
};

#endif // FRAGMENTPROCESSOR_H
