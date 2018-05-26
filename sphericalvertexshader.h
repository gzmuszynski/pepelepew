#ifndef SPHERICALVERTEXSHADER_H
#define SPHERICALVERTEXSHADER_H

#include "vertexprocessor.h"



class SphericalVertexShader : public VertexShader
{
public:
    SphericalVertexShader(VertexProcessor* vp);

    // VertexShader interface
public:
    void process(Vertex &vertex);
};

#endif // SPHERICALVERTEXSHADER_H
