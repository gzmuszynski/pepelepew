#include "fragmentprocessor.h"

FragmentProcessor::FragmentProcessor()
{

}

void FragmentProcessor::rasterize(Buffer &buffer)
{
    float stepX = 1.0f/buffer.width;
    float stepY = 1.0f/buffer.height;

    for(int3 &tri:triangleBuffer)
    {
        Vertex* triangle = new Vertex[3]{vp->vertexBuffer[tri.a], vp->vertexBuffer[tri.b], vp->vertexBuffer[tri.c]};

        float4 bounds = triangleBounds(triangle);

        int minx = qFloor(bounds.x*0.5f+0.5f)*buffer.width;
        int miny = qFloor(bounds.z*0.5f+0.5f)*buffer.height;
        int maxx = qCeil (bounds.y*0.5f+0.5f)*buffer.width;
        int maxy = qCeil (bounds.w*0.5f+0.5f)*buffer.height;
//        int minx = 0, miny = 0, maxx = buffer.width, maxy = buffer.height;

        for(int x = minx; x < maxx; x++)
        {
            for(int y = miny; y < maxy; y++)
            {
                Hit hit = tf(triangle, x * stepX - 0.5f, y * stepY - 0.5f);

                if(hit.test)
                {
                    Fragment f = fragmentShader->process(triangle, hit);
                    if(f.depth.x < buffer.depth[x+y*buffer.width].x && f.depth.x > -1.0f)
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
    float4 normal   = float4(triangle[0].normal * hit.A[0] + triangle[1].normal * hit.A[1] + triangle[2].normal * hit.A[2], 1.0f);
    float4 position = float4(triangle[0].pos    * hit.A[0] + triangle[1].pos    * hit.A[1] + triangle[2].pos    * hit.A[2]);
    float4 depth    = float4((1.0f + position.z) * 0.5f);

    // Inverse Perspective calculation

    position        = float4(position.x*Pi[0][0], position.y*Pi[1][1], -1.0f, position.z*Pi[3][2] + Pi[3][3]);
    position /= position.w;

    return Fragment(color, depth, normal, position);
}
