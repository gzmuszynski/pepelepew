#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H

#include "mat4.h"
#include "mesh.h"

class VertexShader;

class VertexProcessor
{
public:
    VertexProcessor();

    mat4 M;
    mat4 V;
    mat4 P;
    mat4 Pi;
    mat4 MV;
    mat4 MVP;
    mat4 MVT;

    VertexShader* vertexShader;

    QVector<Vertex> vertexBuffer;

    void setIdentity();

    void translate(float4 &vec);
    void rotate   (float a, float4 &vec);
    void scale    (float4 &vec);

    void lookAt   (float4 &eye, float4 &target, float4 &up);
    void perspective(float fov, float ratio, float zNear, float zFar);

    void transform();
};

class VertexShader
{
public:
    VertexShader(VertexProcessor* vp);

    virtual void process(Vertex &vertex);

protected:
    VertexProcessor* vp;

};

#endif // VERTEXPROCESSOR_H
