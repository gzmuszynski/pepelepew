#include "vertexprocessor.h"
#include <QtDebug>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

VertexProcessor::VertexProcessor()
{
    setIdentity();
}

void VertexProcessor::setIdentity()
{
    M   = mat4();
    V   = mat4();
    P   = mat4();
    Pi  = mat4();
    MV  = mat4();
    MVP = mat4();
    MVT = mat4();
}

void VertexProcessor::translate(float3 &vec)
{
    M = glm::translate(M, vec);
}

void VertexProcessor::rotate(float a, float3 &vec)
{
    M = glm::rotate(M, glm::radians(a), vec);
}

void VertexProcessor::scale(float3 &vec)
{
    M = glm::scale(M, vec);
}

void VertexProcessor::lookAt(float3 &eye, float3 &target, float3 &up)
{    
    V = glm::lookAt(eye, target, up);
}

void VertexProcessor::perspective(float fov, float ratio, float zNear, float zFar)
{
    P = glm::perspective(fov, ratio, zNear, zFar);

    Pi[0][0] = 1.0f/P[0][0];
    Pi[1][1] = 1.0f/P[1][1];
    Pi[2][2] = 0;
    Pi[2][3] = -1.0f;
    Pi[3][2] = 1.0f/P[2][3];
    Pi[3][3] = P[2][2]/P[2][3];
}

void VertexProcessor::transform()
{
    MV = V*M;
    MVP = P*MV;
    MVT = glm::transpose(glm::inverse(MVP));

    for(Vertex &v : vertexBuffer)
    {
        vertexShader->process(v);
        //        qDebug() << v.pos.x << v.pos.y << v.pos.z;
    }
}

VertexShader::VertexShader(VertexProcessor *vp) : vp(vp)
{

}

void VertexShader::process(Vertex &vertex)
{

    vertex.pos = vp->MVP * vertex.pos;
    if(vertex.pos.z == 0.0f)
        vertex.pos.w = 0.0001f;
    vertex.pos    /= vertex.pos.w;
    vertex.normal = vp->MVT * float4(vertex.normal, 1.0f);
}
