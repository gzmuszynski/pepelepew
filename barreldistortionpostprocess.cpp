#include "barreldistortionpostprocess.h"

BarrelDistortionPostProcess::BarrelDistortionPostProcess()
{

}

void BarrelDistortionPostProcess::operator ()(Buffer &buffer)
{
    float str = 0.5f;

    float4* old = new float4[buffer.width*buffer.height];
    memcpy(old, buffer.final,sizeof(float4)*buffer.width*buffer.height);

    float tox = buffer.width-1;
    float toy = buffer.height-1;

    float tos = 1.0f/tox;
    float tot = 1.0f/toy;

    for(int x = 0; x < buffer.width; x++)
    {
        for(int y = 0; y < buffer.height; y++)
        {
            float s = x*tos;
            float t = y*tot;

            s = 2.0f * s - 1.0f;
            t = 2.0f * t - 1.0f;

            int x2;
            int y2;

            float theta = glm::atan(s,t);
            float radius = glm::length(glm::vec2(s,t));
            radius = glm::pow(radius,str+1);

            float u = radius * glm::cos(theta);
            float v = radius * glm::sin(theta);

            x2 = (0.5f *  v  + 0.5f) * tox;
            y2 = (0.5f *  u  + 0.5f) * toy;

            if(x2>=0 && x2 < buffer.width && y2>=0 && y2 < buffer.height)
            {
                buffer.final[x+buffer.width*y] = old[x2+buffer.width*y2];
            }
            else
            {
                buffer.final[x+buffer.width*y] = float4(0.0f,0.0f,0.0f,1.0f);
            }
        }
    }

}
