#include "cubicprojection.h"
#include <glm/gtx/rotate_vector.hpp>
#include <QImage>

CubicProjection::CubicProjection(MRTRasterizer *R, int cubeSize):
    MRTProjection(R),
    cubeSize(cubeSize)
{

}

QVector<Buffer> CubicProjection::render(Buffer &buffer, QVector<Mesh> &meshes, Camera &camera, QVector<Material> &materials, QVector<Light> &lights)
{
    n = 6;

    float3 OX(1.0f, 0.0f, 0.0f);
    float3 OY(0.0f, 1.0f, 0.0f);
    float3 OZ(0.0f, 0.0f, 1.0f);

    int w = cubeSize;
    int h = w;

    float fov = camera.fov;


    float3 forward = camera.target - camera.pos;
    float3 side = glm::rotate(forward, glm::radians(90.0f), camera.up);
    float3 up = glm::rotate(forward, glm::radians(90.0f), side);

    QVector<float3> targets;
    targets.push_back(float3( 1.0f, 0.0f, 0.0f));             // right
    targets.push_back(float3(-1.0f, 0.0f, 0.0f));             // left
    targets.push_back(float3( 0.0f, 1.0f, 0.0f));             // front
    targets.push_back(float3( 0.0f,-1.0f, 0.0f));             // back
    targets.push_back(float3( 0.0f, 0.0f, 1.0f));             // up
    targets.push_back(float3( 0.0f, 0.0f,-1.0f));             // down

    QVector<float3> ups;
    ups.push_back(float3( 0.0f, 0.0f, 1.0f));                 // right
    ups.push_back(float3( 0.0f, 0.0f, 1.0f));                 // left
    ups.push_back(float3( 0.0f, 0.0f, 1.0f));                 // front
    ups.push_back(float3( 0.0f, 0.0f, 1.0f));                 // back
    ups.push_back(float3( 0.0f, 1.0f, 0.0f));                 // up
    ups.push_back(float3( 0.0f,-1.0f, 0.0f));                 // down

    buffer.clear();
    QVector<Buffer> renderTargets(n);

    for(int i = 0; i < 6; i++)
    {
        renderTargets[i] = Buffer(w,h);
        renderTargets[i].clear();

        QVector<Light> lightBuffer(lights);

        R->vp->setIdentity();


        R->vp->lookAt(camera.pos, targets[i], ups[i]);
        R->vp->perspective(130.0f, 1.0f, camera.zNear, camera.zFar);

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

            R->vp->lookAt(camera.pos, targets[i], ups[i]);
            R->vp->perspective(126.5f, 1.0f, camera.zNear, camera.zFar);

            R->vp->transform();
            R->fp->rasterize  (renderTargets[i]);
            R->ds->operator ()(renderTargets[i]);
            R->pp->process    (renderTargets[i]);
        }

    }

    return renderTargets;
}

void CubicProjection::project(QVector<Buffer> &renderTargets, Buffer &frameBuffer)
{
    bool debug = false;


    if(debug)
    {
        int w = frameBuffer.width;

        for(int i = 0; i < renderTargets.size(); i++)
        {
            for(int x = 0; x < cubeSize; x++)
            {
                for(int y = 0; y < cubeSize; y++)
                {
                    int xOffset, yOffset;

                    switch(i)
                    {
                    case 0: {xOffset = 0 * cubeSize; yOffset = 1 * cubeSize; break;} // right
                    case 1: {xOffset = 2 * cubeSize; yOffset = 1 * cubeSize; break;} // left
                    case 2: {xOffset = 3 * cubeSize; yOffset = 1 * cubeSize; break;} // front
                    case 3: {xOffset = 1 * cubeSize; yOffset = 1 * cubeSize; break;} // back
                    case 4: {xOffset = 1 * cubeSize; yOffset = 2 * cubeSize; break;} // up
                    case 5: {xOffset = 1 * cubeSize; yOffset = 0 * cubeSize; break;} // down
                    }
                    //                    int fbCoords = xOffset + x + (y + yOffset) * w;
                    int rtCoords = x + y*cubeSize;
                    int fbCoords = x + xOffset + (y+yOffset)*w;

                    frameBuffer.final   [fbCoords] = renderTargets[i].final   [rtCoords];
                    frameBuffer.color   [fbCoords] = renderTargets[i].color   [rtCoords];
                    frameBuffer.normal  [fbCoords] = renderTargets[i].normal  [rtCoords];
                    frameBuffer.depth   [fbCoords] = renderTargets[i].depth   [rtCoords];
                    frameBuffer.position[fbCoords] = renderTargets[i].position[rtCoords];

                }
            }
        }
    }
    else
    {
        int w = frameBuffer.width;
        int h = frameBuffer.height;

        int wn = renderTargets[0].width;

        float tox = w-1;
        float toy = h-1;

        float tos = 1.0f/tox;
        float tot = 1.0f/toy;

        for(int x = 0; x < frameBuffer.width; x++)
        {
            for(int y = 0; y < frameBuffer.height; y++)
            {
                float s = x*tos;
                float t = y*tot;

//                s = 2.0f * s - 1.0f;
                t = 1.0f * t - 1.0f;

                int x2;
                int y2;

                float theta = t * M_PI;
                float phi = s * 2 * M_PI;

                float X = glm::sin(phi) * glm::sin(theta) * -1.0f;
                float Y = glm::cos(theta);
                float Z = glm::cos(phi) * glm::sin(theta) * -1.0f;

                float xa, ya, za;
                float a = glm::max(glm::abs(X), glm::max(glm::abs(Y), glm::abs(Z)));

                xa = X/a;
                ya = Y/a;
                za = Z/a;

                float u = phi;
                float v = theta;

                x2 = (0.5f *  v  + 0.5f) * (wn-1);
                y2 = (0.5f *  u  + 0.5f) * (wn-1);

                int fbCoords = x + y * w;
                int rtCoords = x2 + y2 * wn;

                int i = 2;

                if (xa == 1)
                {
                    //Right
                    i = 1;
                    x2 = (int)((((za + 1.0f) / 2.0f) - 1.0f) * cubeSize);
                    y2 = (int)((((ya + 1.0f) / 2.0f)) * cubeSize);
                }
                else if (xa == -1)
                {
                    //Left
                    i = 0;
                    x2 = (int)((((za + 1.0f) / 2.0f)) * cubeSize);
                    y2 = (int)((((ya + 1.0f) / 2.0f)) * cubeSize);
                }
                else if (ya == 1)
                {
                    //Up
                    i = 4;
                    x2 = (int)((((xa + 1.0f) / 2.0f)) * cubeSize);
                    y2 = (int)((((za + 1.0f) / 2.0f)- 1.0f) * cubeSize);
                }
                else if (ya == -1)
                {
                    //Down
                    i = 5;
                    x2 = (int)((((xa + 1.0f) / 2.0f)) * cubeSize);
                    y2 = (int)((((za + 1.0f) / 2.0f)) * cubeSize);
                }
                else if (za == 1)
                {
                    //Front
                    i = 3;
                    x2 = (int)((((xa + 1.0f) / 2.0f)) * cubeSize);
                    y2 = (int)((((ya + 1.0f) / 2.0f)) * cubeSize);
                }
                else if (za == -1)
                {
                    //Back
                    i = 2;
                    x2 = (int)((((xa + 1.0f) / 2.0f) - 1.0f) * cubeSize);
                    y2 = (int)((((ya + 1.0f) / 2.0f)) * cubeSize);
                }
                else
                {
                    x2 = 0;
                    y2 = 0;
                }

                x2 = glm::abs(x2);
                y2 = glm::abs(y2);

                rtCoords = x2 + y2 * wn;

                if (x2 < cubeSize && y2 < cubeSize && x2 >= 0 && y2 >= 0)
                {
                    frameBuffer.final   [fbCoords] = renderTargets[i].final   [rtCoords];
                    frameBuffer.color   [fbCoords] = renderTargets[i].color   [rtCoords];
                    frameBuffer.normal  [fbCoords] = renderTargets[i].normal  [rtCoords];
                    frameBuffer.depth   [fbCoords] = renderTargets[i].depth   [rtCoords];
                    frameBuffer.position[fbCoords] = renderTargets[i].position[rtCoords];
                }
            }
        }
    }
}
