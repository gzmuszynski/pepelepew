#ifndef CURVILINEARVERTEXSHADER2_H
#define CURVILINEARVERTEXSHADER2_H

#include "vertexprocessor.h"



class CurvilinearVertexShader2 : public VertexShader
{
public:
    CurvilinearVertexShader2(VertexProcessor* vp);
    
    // VertexShader interface
public:
    void process(Vertex &vertex);
};

#endif // CURVILINEARVERTEXSHADER2_H
