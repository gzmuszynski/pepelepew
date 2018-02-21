#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(float3 pos, float3 target, float3 up, float fov, float zNear, float zFar) :
    pos(pos),
    target(target),
    up(up),
    fov(fov),
    zNear(zNear),
    zFar(zFar)
{

}
