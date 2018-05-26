#ifndef LIGHT_H
#define LIGHT_H
#include "float4.h"


class Light
{
public:
    Light();
    Light(float4 position, float3 direction = float3(0.0f));

    float3 getVector(float3 &point);
    float getAttenuation(float3 &point);

    bool type;
    float4 position;
    float3 direction;

    float3 ambient;
    float3 diffuse;
    float3 specular;

    float angle                = 0.0f;
    float attenuationLinear    = 0.0f;
    float attenuationQuadratic = 0.0f;
    float spotExponent         = 0.0f;

};

#endif // LIGHT_H
