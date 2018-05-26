#include "light.h"

Light::Light():
    position(float4(0.0f)),
    direction(float3(0.0f))
{

}

Light::Light(float4 position, float3 direction) :
    position(position),
    direction(direction),
    type(position.w == 1.0f),
    ambient(0.1f,0.1f,0.1f),
    diffuse(1.0f,1.0f,1.0f),
    specular(1.0f,1.0f,1.0f)
{

}

float3 Light::getVector(float3 &point)
{
    if(type) // type == omni
    {
        return (float3(position)-point);
    }
    else // type == directional
    {
        return direction;
    }
}

float Light::getAttenuation(float3 &point)
{
    if(type && direction.length() != 0.0f)
    {
        float dist = point.length();

        float aL = dist * attenuationLinear;
        float aQ = dist * attenuationQuadratic;

        float attenuation = 1.0f / (1.0f  + aL + aQ*aQ);

        if(angle == 0)
            return attenuation;

        float DdotV = glm::dot(normalize(direction),-normalize(point));

        if(DdotV < glm::radians(90 - angle))
            return 0.0f;

        return glm::max(0.0f, glm::pow(DdotV, spotExponent) * attenuation);

    }
}
