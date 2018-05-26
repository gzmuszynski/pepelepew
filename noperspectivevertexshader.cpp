#include "noperspectivevertexshader.h"

NoPerspectiveVertexShader::NoPerspectiveVertexShader(VertexProcessor *vp) : VertexShader(vp)
{

}

void NoPerspectiveVertexShader::process(Vertex &vertex)
{
    vertex.pos = vp->MV * vertex.pos;
    float w = vertex.pos.z;
    vertex.pos = vp->P * vertex.pos;

    float tmp = vertex.pos.w;
    vertex.pos /= vertex.pos.w;
    vertex.pos.w = w;
    vertex.normal = vp->MVT * float4(vertex.normal, 1.0f);
}
