#ifndef NOPERSPECTIVEVERTEXSHADER_H
#define NOPERSPECTIVEVERTEXSHADER_H

#include "vertexprocessor.h"



class NoPerspectiveVertexShader : public VertexShader
{
public:
    NoPerspectiveVertexShader(VertexProcessor *vp);

    // VertexShader interface
public:
    void process(Vertex &vertex);
};

#endif // NOPERSPECTIVEVERTEXSHADER_H
