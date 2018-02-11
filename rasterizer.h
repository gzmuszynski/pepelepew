#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "buffer.h"
#include "camera.h"
#include "fragmentprocessor.h"
#include "vertexprocessor.h"



class Rasterizer
{
public:
    Rasterizer();

    void operator()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera);
    
private:
    VertexProcessor* vp;
    FragmentProcessor* fp;
};

#endif // RASTERIZER_H
