#include "rasterizer.h"

float4 OX(1.0f, 0.0f, 0.0f);
float4 OY(0.0f, 1.0f, 0.0f);
float4 OZ(0.0f, 0.0f, 1.0f);

Rasterizer::Rasterizer():
    vp(new VertexProcessor()),
    fp(new FragmentProcessor())
{
    vp->vertexShader = new VertexShader(vp);
    fp->fragmentShader = new FragmentShader(fp);

}

void Rasterizer::operator()(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera)
{
    buffer.clear();

    for(Mesh &mesh:meshes)
    {

        QVector<Vertex> vertexBuffer(mesh.verts);
        QVector<int3> &tris = mesh.tris;


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
    }
}
