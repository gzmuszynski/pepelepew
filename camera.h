#ifndef CAMERA_H
#define CAMERA_H
#include "float4.h"

class Camera
{
public:
    Camera();
    Camera(float3 pos, float3 target, float3 up, float fov, float zNear, float zFar);

    float3 pos;
    float3 target;
    float3 up;

    float fov;
    float zNear;
    float zFar;
};

#endif // CAMERA_H
