#ifndef MRTRASTERIZER_H
#define MRTRASTERIZER_H

#include "rasterizer.h"

class MRTProjection;

class MRTRasterizer : public Rasterizer
{
public:
    MRTRasterizer(int projection = 0, int projectionPieces = 512);

    // Rasterizer interface
public:
    void operator ()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights);

protected:
    MRTProjection* mp;
    QVector<Buffer> renderTargets;
};

class MRTProjection
{
public:
    MRTProjection(MRTRasterizer *R);
    MRTProjection(MRTRasterizer *R, int n);

    virtual QVector<Buffer> render(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights);
    virtual void project(QVector<Buffer> &renderTargets, Buffer &frameBuffer);

protected:
    int n;
    MRTRasterizer *R;
};

#endif // MRTRASTERIZER_H
