#include "deferredshading.h"

DeferredShading::DeferredShading()
{
}


void DeferredShading::operator ()(Buffer &buffer)
{
    for(int x = 0; x < buffer.width; x++)
    {
        for(int y = 0; y < buffer.height; y++)
        {
            float3 color = buffer.color[x+y*buffer.width];
            float3 V = normalize(buffer.position[x+y*buffer.width]);
            float3 N = normalize(buffer.normal[x+y*buffer.width]);
            float depth = buffer.depth[x+y*buffer.width].x;

            float4 final(0.0f, 0.0f, 0.0f, 1.0f);
            for(Light light : lights)
            {
                float3 L = -light.getVector(V);
                float att = light.getAttenuation(V);

                float3 ambient = light.ambient * color;
                float3 diffuse = color * light.diffuse * glm::max(0.0f, glm::dot(N, L)) * att;

                float3 H = normalize(L+V);
                float NdotH = glm::max(0.0f, glm::dot(N, H));

                float3 specular = light.specular * glm::pow(NdotH, 4.0f);

                final += float4(ambient + diffuse + specular, 0.0f);

            }
            //            final = color - depth;
            buffer.final[x+y*buffer.width] = final;
        }
    }
}
