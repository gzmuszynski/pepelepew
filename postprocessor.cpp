#include "postprocessor.h"

PostProcessor::PostProcessor()
{

}

void PostProcessor::process(Buffer &buffer)
{
    for(PostProcess postProcess: postProcesses)
    {
        postProcess(buffer);
    }
}

void PostProcess::operator()(Buffer &buffer)
{
    for(int x = 0; x < buffer.width; x++)
    {
        for(int y = 0; y < buffer.height; y++)
        {
            float4 color = buffer.color[x+y*buffer.width];
            float3 position = buffer.position[x+y*buffer.width];
            float3 normal = normalize(buffer.normal[x+y*buffer.width]);
            float depth = buffer.depth[x+y*buffer.width].x;

            float4 final(0.0f, 0.0f, 0.0f, 0.0f);
            final = color * qMax(0.0f,glm::dot(normalize(position),normal)) * qMin(1.0f, 1.0f - depth * 0.5f);

//            final = color - depth;
            buffer.final[x+y*buffer.width] = final;
        }
    }
}
