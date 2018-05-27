#ifndef CUBICPROJECTION_H
#define CUBICPROJECTION_H

#include "mrtrasterizer.h"



class CubicProjection : public MRTProjection
{
public:
    CubicProjection(MRTRasterizer *R,int cubeSize);

    // MRTProjection interface
public:
    QVector<Buffer> render(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights);
    void project(QVector<Buffer> &renderTargets, Buffer &frameBuffer);
protected:
    int cubeSize;
};

#endif // CUBICPROJECTION_H
