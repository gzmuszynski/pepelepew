#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "buffer.h"
#include "camera.h"
#include "deferredshading.h"
#include "fragmentprocessor.h"
#include "light.h"
#include "postprocessor.h"
#include "vertexprocessor.h"



class Rasterizer
{
public:
    Rasterizer(int vertexShader = 0, int postProcess = 0);
    Rasterizer(QVector<Light> &lights);

    virtual void operator()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights);
    
//private:
    VertexProcessor* vp;
    FragmentProcessor* fp;
    DeferredShading* ds;
    PostProcessor* pp;
};

#endif // RASTERIZER_H
