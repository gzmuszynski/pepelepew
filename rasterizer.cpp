#include "rasterizer.h"
#include "deferredshading.h"
#include "noperspectivevertexshader.h"
#include "curvilinearvertexshader.h"
#include "barreldistortionpostprocess.h"
#include "sphericalvertexshader.h"
#include "curvilinearvertexshader2.h"
#include "barreldistortiontanpostprocess.h"

float3 OX(1.0f, 0.0f, 0.0f);
float3 OY(0.0f, 1.0f, 0.0f);
float3 OZ(0.0f, 0.0f, 1.0f);

Rasterizer::Rasterizer(int vertexShader, int post):
    vp(new VertexProcessor()),
    fp(new FragmentProcessor()),
    pp(new PostProcessor()),
    ds(new DeferredShading())
{
    int vs = vertexShader;
    int fs = 0;
    int tf = 0;
    int ps = post;

    switch(vs)
    {
//    case 1 : {vp->vertexShader = new NoPerspectiveVertexShader(vp); break;}
    case 2 : {vp->vertexShader = new CurvilinearVertexShader(vp);   break;}
    case 3 : {vp->vertexShader = new SphericalVertexShader(vp); break;}
//    case 4 : {vp->vertexShader = new CurvilinearVertexShader2(vp);   break;}

    default: {vp->vertexShader = new VertexShader(vp);              break;}
    }

    switch(fs)
    {
    default: {fp->fragmentShader = new FragmentShader(fp); break;}
    }

    switch(tf)
    {
    case 1 : {fp->triangleFunction = new CurvilinearTriangleFunction(); break;}
    default: {fp->triangleFunction = new TriangleFunction(); break;}
    }

    switch(ps)
    {
    case 1: { pp->postProcesses.push_back(new BarrelDistortionPostProcess()); break;}
    case 2: { pp->postProcesses.push_back(new BarrelDistortionTanPostProcess()); break;}
    default: {break;}
    }

    fp->vp = vp;
}

Rasterizer::Rasterizer(QVector<Light> &lights):
    Rasterizer()
{

}

void Rasterizer::operator()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials,QVector<Light> &lights)
{
    buffer.clear();
    QVector<Light> lightBuffer(lights);

    vp->setIdentity();

    vp->lookAt(camera.pos, camera.target, camera.up);
    vp->perspective(camera.fov, buffer.width*1.0f/buffer.height, camera.zNear, camera.zFar);

    vp->transformLights(lightBuffer);
    ds->lights = lightBuffer;
    fp->materialBuffer = materials;

    for(Mesh &mesh:meshes)
    {

        QVector<Vertex> vertexBuffer(mesh.verts);
        QVector<int4> &tris = mesh.tris;


        vp->vertexBuffer = vertexBuffer;
        fp->triangleBuffer = tris;

        vp->setIdentity();

        vp->scale(mesh.Sv);

        vp->rotate(mesh.Rv.x, OX);
        vp->rotate(mesh.Rv.y, OY);
        vp->rotate(mesh.Rv.z, OZ);

        vp->translate(mesh.Tv);

        vp->lookAt(camera.pos, camera.target, camera.up);
        vp->perspective(camera.fov, buffer.width*1.0f/buffer.height, camera.zNear, camera.zFar);

        vp->transform();
        fp->rasterize(buffer);
        ds->operator ()(buffer);
        pp->process(buffer);
    }
}
