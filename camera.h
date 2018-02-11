#ifndef CAMERA_H
#define CAMERA_H
#include "float4.h"

class Camera
{
public:
    Camera();
    Camera(float4 pos, float4 target, float4 up, float fov, float zNear, float zFar);

    float4 pos;
    float4 target;
    float4 up;

    float fov;
    float zNear;
    float zFar;
};

#endif // CAMERA_H
