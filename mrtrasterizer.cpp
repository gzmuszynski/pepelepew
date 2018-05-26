#include "cubicprojection.h"
#include "mrtrasterizer.h"
#include <glm/gtx/rotate_vector.hpp>



MRTRasterizer::MRTRasterizer()

{
    vp = new VertexProcessor();
    fp = new FragmentProcessor();
    pp = new PostProcessor();
    ds = new DeferredShading();

    vp->vertexShader     = new VertexShader(vp);
    fp->fragmentShader   = new FragmentShader(fp);
    fp->vp = vp;
    fp->triangleFunction = new TriangleFunction();

    int projection = 0;
    switch(projection)
    {
    case 0 : {mp = new CubicProjection(this); break;}
    default: {mp = new MRTProjection(this, projection); break;}
    }
}

void MRTRasterizer::operator ()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights)
{
    renderTargets = mp->render(buffer, meshes, camera, materials, lights);
    mp->project(renderTargets, buffer);
}

// MRT PROJECTION STARTS HERE

MRTProjection::MRTProjection(MRTRasterizer *R) : R(R)
{

}

MRTProjection::MRTProjection(MRTRasterizer *R, int n) : MRTProjection(R)
{
    if(n>0)
        this->n = n;
    else
        this->n = 1;
}

QVector<Buffer> MRTProjection::render(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights)
{
    float3 OX(1.0f, 0.0f, 0.0f);
    float3 OY(0.0f, 1.0f, 0.0f);
    float3 OZ(0.0f, 0.0f, 1.0f);

    int w = buffer.width;
    int h = buffer.height;

    int wn = glm::floor(w * 1.0f / n);
    float ratio =  wn*1.0f/h;

    float fov = camera.fov;
    float fovStep = fov / n;


    float3 forward = camera.target - camera.pos;
    float3 f = glm::rotate(forward, glm::radians((fov-fovStep)*0.5f), camera.up);

    buffer.clear();
    QVector<Buffer> renderTargets(n);

    for(int i = 0; i < n; i++)
    {
        renderTargets[i] = Buffer(wn,h);
        renderTargets[i].clear();

        QVector<Light> lightBuffer(lights);

        R->vp->setIdentity();

        float3 target = camera.pos + glm::rotate(f, glm::radians(-fovStep*i),camera.up);

        R->vp->lookAt(camera.pos, target, camera.up);
        R->vp->perspective(10, ratio, camera.zNear, camera.zFar);

        R->vp->transformLights(lightBuffer);
        R->ds->lights = lightBuffer;
        R->fp->materialBuffer = materials;

        for(Mesh &mesh:meshes)
        {

            QVector<Vertex> vertexBuffer(mesh.verts);
            QVector<int4> &tris = mesh.tris;


            R->vp->vertexBuffer = vertexBuffer;
            R->fp->triangleBuffer = tris;

            R->vp->setIdentity();

            R->vp->scale(mesh.Sv);

            R->vp->rotate(mesh.Rv.x, OX);
            R->vp->rotate(mesh.Rv.y, OY);
            R->vp->rotate(mesh.Rv.z, OZ);

            R->vp->translate(mesh.Tv);

            R->vp->lookAt(camera.pos, target, camera.up);
            R->vp->perspective(fov/2, ratio, camera.zNear, camera.zFar);

            R->vp->transform();
            R->fp->rasterize  (renderTargets[i]);
            R->ds->operator ()(renderTargets[i]);
            R->pp->process    (renderTargets[i]);
        }

    }

    return renderTargets;
}

void MRTProjection::project(QVector<Buffer> &renderTargets, Buffer &frameBuffer)
{
    int w = frameBuffer.width;
    int h = frameBuffer.height;

    int wn = renderTargets[0].width;


    for(int i = 0; i < renderTargets.size(); i++)
    {
        for(int x = 0; x < renderTargets[i].width; x++)
        {
            for(int y = 0; y < h; y++)
            {
                int fbCoords = i*wn + x + y*w;
                int rtCoords = x + y*wn;

                frameBuffer.final   [fbCoords] = renderTargets[i].final   [rtCoords];
                frameBuffer.color   [fbCoords] = renderTargets[i].color   [rtCoords];
                frameBuffer.normal  [fbCoords] = renderTargets[i].normal  [rtCoords];
                frameBuffer.depth   [fbCoords] = renderTargets[i].depth   [rtCoords];
                frameBuffer.position[fbCoords] = renderTargets[i].position[rtCoords];
            }
        }

    }
}
