#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vertex.h>
class Hit
{
public:
    Hit() : test(false), A(0.0f) {}
    bool test;
    float4 A;
};

class TriangleFunction
{
public:
    TriangleFunction();

    virtual Hit operator()(Vertex* &V, float x, float y);
};

#endif // TRIANGLE_H
