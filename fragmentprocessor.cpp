#include "fragmentprocessor.h"

FragmentProcessor::FragmentProcessor()
{

}

void FragmentProcessor::rasterize(Buffer &buffer)
{
    float stepX = 2.0f/buffer.width;
    float stepY = 2.0f/buffer.height;

    for(int3 &tri:triangleBuffer)
    {
        Vertex* triangle = new Vertex[3]{vp->vertexBuffer[tri.a], vp->vertexBuffer[tri.b], vp->vertexBuffer[tri.c]};

        float4 bounds = triangleBounds(triangle);

        int minx = qFloor(bounds[0])*buffer.width;
        int miny = qFloor(bounds[2])*buffer.height;
        int maxx = qCeil (bounds[1])*buffer.width;
        int maxy = qCeil (bounds[3])*buffer.height;

        for(int x = minx; x < maxx; x++)
        {
            for(int y = miny; y < maxy; y++)
            {
                Hit hit = tf(triangle, (x - 0.5f) * stepX, (y - 0.5f) * stepY);

                if(hit.test)
                {
                    Fragment f = fragmentShader->process(triangle, hit);
                    if(f.depth.x > buffer.depth[x+y*buffer.width].x)
                    {
                        buffer.color   [x+y*buffer.width] = f.color;
                        buffer.depth   [x+y*buffer.width] = f.depth;
                        buffer.normal  [x+y*buffer.width] = f.normal;
                        buffer.position[x+y*buffer.width] = f.position;
                    }
                }
            }
        }
    }
}

float4 FragmentProcessor::triangleBounds(Vertex *&triangle)
{
    float minx = qBound(-1.0f, qMin(triangle[0].pos.x,qMin(triangle[1].pos.x,triangle[2].pos.x)), 1.0f);
    float maxx = qBound(-1.0f, qMax(triangle[0].pos.x,qMax(triangle[1].pos.x,triangle[2].pos.x)), 1.0f);

    float miny = qBound(-1.0f, qMin(triangle[0].pos.y,qMin(triangle[1].pos.y,triangle[2].pos.y)), 1.0f);
    float maxy = qBound(-1.0f, qMax(triangle[0].pos.y,qMax(triangle[1].pos.y,triangle[2].pos.y)), 1.0f);

    return float4(minx, maxx, miny, maxy);
}

FragmentShader::FragmentShader(FragmentProcessor *fp) : fp(fp)
{

}

Fragment FragmentShader::process(Vertex *&triangle, Hit &hit)
{
    mat4 Pi = fp->vp->Pi;

    float4 color    = float4(1.0f);
    float4 normal   = float4(triangle[0].normal * hit.A[0] + triangle[1].normal * hit.A[1] + triangle[2].normal * hit.A[2]);
    float4 position = float4(triangle[0].pos    * hit.A[0] + triangle[1].pos    * hit.A[1] + triangle[2].pos    * hit.A[2]);
    float4 depth    = float4(position.z);
    position        = float4(position.x*Pi[0][0], position.y*Pi[1][1], -1.0f, position.z*Pi[3][2] + Pi[3][3]);

    return Fragment(color, depth, normal, position);
}
