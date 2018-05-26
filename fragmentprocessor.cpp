#include "fragmentprocessor.h"

FragmentProcessor::FragmentProcessor()
{

}

void FragmentProcessor::rasterize(Buffer &buffer)
{
    float stepX = 1.0f/buffer.width;
    float stepY = 1.0f/buffer.height;

    for(int4 &tri:triangleBuffer)
    {
        Vertex* triangle = new Vertex[3]{vp->vertexBuffer[tri.a], vp->vertexBuffer[tri.b], vp->vertexBuffer[tri.c]};

        float4 bounds = triangleBounds(triangle);

        int minx = glm::floor(bounds.x*0.5f+0.5f)*buffer.width;
        int miny = glm::floor(bounds.z*0.5f+0.5f)*buffer.height;
        int maxx = glm::ceil (bounds.y*0.5f+0.5f)*buffer.width;
        int maxy = glm::ceil (bounds.w*0.5f+0.5f)*buffer.height;
//        minx = 0, miny = 0, maxx = buffer.width, maxy = buffer.height;

        for(int x = minx; x < maxx; x++)
        {
            for(int y = miny; y < maxy; y++)
            {
                Hit hit = triangleFunction->operator ()(triangle, x * stepX - 0.5f, y * stepY - 0.5f);

                if(hit.test)
                {
                    Fragment f = fragmentShader->process(triangle, hit, materialBuffer[tri.m]);
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

    float minx = glm::clamp(glm::min(triangle[0].pos.x,glm::min(triangle[1].pos.x,triangle[2].pos.x)),-1.0f,  1.0f);
    float maxx = glm::clamp(glm::max(triangle[0].pos.x,glm::max(triangle[1].pos.x,triangle[2].pos.x)),-1.0f,  1.0f);

    float miny = glm::clamp(glm::min(triangle[0].pos.y,glm::min(triangle[1].pos.y,triangle[2].pos.y)),-1.0f,  1.0f);
    float maxy = glm::clamp(glm::max(triangle[0].pos.y,glm::max(triangle[1].pos.y,triangle[2].pos.y)),-1.0f,  1.0f);

    return float4(minx, maxx, miny, maxy);
}

FragmentShader::FragmentShader(FragmentProcessor *fp) : fp(fp)
{

}

Fragment FragmentShader::process(Vertex *&triangle, Hit &hit, Material &material)
{
    mat4 Pi = fp->vp->Pi;

    float3 pc = float3(hit.A[0]*(triangle[0].pos.z*Pi[3][2] + Pi[3][3]),
                       hit.A[1]*(triangle[1].pos.z*Pi[3][2] + Pi[3][3]),
                       hit.A[2]*(triangle[2].pos.z*Pi[3][2] + Pi[3][3]));

    float3 coords = ((triangle[0].coord * pc[0] + triangle[1].coord * pc[1] + triangle[2].coord * pc[2]) / (pc[0] + pc[1] + pc[2]));

    float4 color    = float4(material.diffuseColor * sample2DTexture(coords.x, coords.y, material.diffuseTexture));
    float4 normal   = float4((triangle[0].normal * pc[0] + triangle[1].normal * pc[1] + triangle[2].normal * pc[2]) / (pc[0] + pc[1] + pc[2]), 1.0f);
    float4 position = float4(triangle[0].pos    * hit.A[0] + triangle[1].pos    * hit.A[1] + triangle[2].pos    * hit.A[2]);
    float4 depth    = float4((1.0f + position.z) * 0.5f);

    // Inverse Perspective calculation

    position        = float4(position.x*Pi[0][0], position.y*Pi[1][1], -1.0f, position.z*Pi[3][2] + Pi[3][3]);
    position /= position.w;

    return Fragment(color, depth, normal, position);
}
