#include "sphericalvertexshader.h"

SphericalVertexShader::SphericalVertexShader(VertexProcessor *vp) : VertexShader(vp)
{

}

void SphericalVertexShader::process(Vertex &vertex)
{
    float near = -(2.0f*vp->P[2].w)/(2.0f*vp->P[2].z-2.0f);
    float far = -((vp->P[2].z-1.0f)*near)/(vp->P[2].z+1.0);

    vertex.pos = vertex.pos *vp->MV;

    float fovy = glm::radians(90.0f);
    float fovx = glm::radians(360.0f);

    float ro = glm::length(vertex.pos);

    float x = glm::atan(vertex.pos.x,vertex.pos.z)/fovx;
    float y = std::sin(-vertex.pos.y/ro)/fovy;
    float z = (ro-near)/(far-near);

    vertex.pos = float4(x,y,z,1.0f);
}
