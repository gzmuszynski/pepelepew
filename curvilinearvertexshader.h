#ifndef CURVILINEARVERTEXSHADER_H
#define CURVILINEARVERTEXSHADER_H

#include "vertexprocessor.h"



class CurvilinearVertexShader : public VertexShader
{
public:
    CurvilinearVertexShader(VertexProcessor* vp);

    // VertexShader interface
public:
    void process(Vertex &vertex);
};

#endif // CURVILINEARVERTEXSHADER_H
