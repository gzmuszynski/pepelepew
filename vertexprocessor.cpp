#include "vertexprocessor.h"

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

void VertexProcessor::translate(float4 &vec)
{
    M *= mat4(float4(1.0f, 0.0f, 0.0f, vec.x),
              float4(0.0f, 1.0f, 0.0f, vec.y),
              float4(0.0f, 0.0f, 1.0f, vec.z),
              float4(0.0f, 0.0f, 0.0f, 1.0f ));
}

void VertexProcessor::rotate(float a, float4 &vec)
{
    float s = std::sin(a*rad);
    float c = std::cos(a*rad);

    vec.normalize();

    M *= mat4(float4(vec.x*vec.x*(1.0f - c) + c       , vec.x*vec.y*(1.0f - c) - vec.z*s , vec.x*vec.z*(1.0f - c) + vec.y*s , 0.0f ),
              float4(vec.x*vec.y*(1.0f - c) + vec.z*s , vec.y*vec.y*(1.0f - c) + c       , vec.z*vec.y*(1.0f - c) - vec.x*s , 0.0f ),
              float4(vec.x*vec.z*(1.0f - c) - vec.y*s , vec.z*vec.y*(1.0f - c) + vec.x*s , vec.z*vec.z*(1.0f - c) + c       , 0.0f ),
              float4(0.0f	                          , 0.0f                             , 0.0f                             , 1.0f ));
}

void VertexProcessor::scale(float4 &vec)
{
    M *= mat4(float4(vec.x, 0.0f,  0.0f,  0.0f),
              float4(0.0f,  vec.y, 0.0f,  0.0f),
              float4(0.0f,  0.0f,  vec.z, 0.0f),
              float4(0.0f,  0.0f,  0.0f,  1.0f));
}

void VertexProcessor::lookAt(float4 &eye, float4 &target, float4 &up)
{
    up.normalize();

    float4 forward = (eye - target).normalize();
    float4 left    = crossProduct(up, forward).normalize();
                up = crossProduct(forward, left);

    V = mat4(float4( left.x    , left.y    , left.z    , -dotProduct(left,eye) ),
             float4( up.x      , up.y      ,  up.z     , -dotProduct(up,eye) ),
             float4( forward.x , forward.y , forward.z , -dotProduct(forward,eye) ),
             float4( 0.0f      , 0.0f      , 0.0f      , 1.0f ));
}

void VertexProcessor::perspective(float fov, float ratio, float zNear, float zFar)
{
    if (zFar == zNear)
            return;
        float f_n = 1.0f / (zNear - zFar);
        ratio     = 1.0f / ratio;

        fov      *= 2.0f*rad;

        float s   = std::sin(fov);
        float f   = s != 0.0f ? std::cos(fov) / s : std::cos(fov) / 0.0001f;

        P[0][0] = f*ratio;
        P[1][1] = f;
        P[2][2] = (zFar+zNear)*f_n;
        P[2][3] = (zFar*zNear)*f_n * 2.0f;
        P[3][2] = -1.0f;
        P[3][3] = 0.0f;

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
    MVT = transpose(inverse(MVP));

    for(Vertex &v : vertexBuffer)
    {
        vertexShader->process(v);
    }
}

VertexShader::VertexShader(VertexProcessor *vp) : vp(vp)
{

}

void VertexShader::process(Vertex &vertex)
{
    vertex.pos    *= vp->MVP;
    vertex.pos    /= vertex.pos.w;
    vertex.normal *= vp->MVT;
}
