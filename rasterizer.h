#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "buffer.h"
#include "camera.h"
#include "fragmentprocessor.h"
#include "postprocessor.h"
#include "vertexprocessor.h"



class Rasterizer
{
public:
    Rasterizer();

    void operator()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera);
    
private:
    VertexProcessor* vp;
    FragmentProcessor* fp;
    PostProcessor* pp;
};

#endif // RASTERIZER_H
