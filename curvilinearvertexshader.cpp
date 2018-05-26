#include "curvilinearvertexshader.h"
#include "QtDebug"

CurvilinearVertexShader::CurvilinearVertexShader(VertexProcessor *vp) : VertexShader(vp)
{

}

void CurvilinearVertexShader::process(Vertex &vertex)
{
    vertex.pos = vp->MV * vertex.pos;
    vertex.pos.z = 0.4f * (vertex.pos.z - glm::length(float3(vertex.pos)));
    vertex.pos = vp->P * vertex.pos;
    if(vertex.pos.z == 0.0f)
        vertex.pos.w = 0.0001f;
    vertex.pos    /= vertex.pos.w;
    vertex.normal = vp->MVT * float4(vertex.normal, 1.0f);
}
