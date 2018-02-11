#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(float4 pos, float4 target, float4 up, float fov, float zNear, float zFar) :
    pos(pos),
    target(target),
    up(up),
    fov(fov),
    zNear(zNear),
    zFar(zFar)
{

}
