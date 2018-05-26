#include "curvilinearvertexshader2.h"

CurvilinearVertexShader2::CurvilinearVertexShader2(VertexProcessor *vp) : VertexShader(vp)
{
}

void CurvilinearVertexShader2::process(Vertex &vertex)
{
    vertex.pos = vp->MV * vertex.pos;
    float z0 = vertex.pos.z;
    vertex.pos.z = 0.5f * (vertex.pos.z - glm::length(float3(vertex.pos)));
    vertex.pos = vp->P * vertex.pos;
    if(vertex.pos.z == 0.0f)
        vertex.pos.w = 0.0001f;
    vertex.pos    /= vertex.pos.w;
    vertex.pos.z = z0;
    vertex.normal = vp->MVT * float4(vertex.normal, 1.0f);
}
