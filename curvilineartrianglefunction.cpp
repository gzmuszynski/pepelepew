#include "curvilineartrianglefunction.h"

CurvilinearTriangleFunction::CurvilinearTriangleFunction()
{

}

Hit CurvilinearTriangleFunction::operator()(Vertex *&V, float x, float y)
{
    Hit hit;

    float d[3] = {1.0f,
                  1.0f,
                  1.0f};

    float xy[3] = {-0.5f*(V[0].pos.w - glm::length(float3(x,y,V[0].pos.w))),
                   -0.5f*(V[1].pos.w - glm::length(float3(x,y,V[1].pos.w))),
                   -0.5f*(V[2].pos.w - glm::length(float3(x,y,V[2].pos.w)))};

    float ABy = V[0].pos.y * d[0] - V[1].pos.y * d[1];
    float ABx = V[0].pos.x * d[0] - V[1].pos.x * d[1];
    float BCy = V[1].pos.y * d[1] - V[2].pos.y * d[2];
    float CBx = V[2].pos.x * d[2] - V[1].pos.x * d[1];
    float ACx = V[0].pos.x * d[0] - V[2].pos.x * d[2];
    float CAy = V[2].pos.y * d[2] - V[0].pos.y * d[0];

    float xa =  x * xy[1] - V[0].pos.x * d[0];
    float ya =  y * xy[1] - V[0].pos.y * d[0];

    float xb =  x * xy[2] - V[1].pos.x * d[1];
    float yb =  y * xy[2] - V[1].pos.y * d[1];

    float xc =  x * xy[0] - V[2].pos.x * d[2];
    float yc =  y * xy[0] - V[2].pos.y * d[2];

    float AB =  ABx * ya - ABy * xa;
    float BC = -CBx * yb - BCy * xb;
    float CA = -ACx * yc - CAy * xc;

    hit.test = ((AB < 0.0f || (AB == 0.0f && (ABy < 0.0f || (ABy == 0.0f && ABx < 0.0f)))) &&
                (BC < 0.0f || (BC == 0.0f && (BCy < 0.0f || (BCy == 0.0f && CBx > 0.0f)))) &&
                (CA < 0.0f || (CA == 0.0f && (CAy < 0.0f || (CAy == 0.0f && ACx > 0.0f)))) );

    if( hit.test )
    {
        hit.A[0] = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx) + (CBx * -CAy));
        hit.A[1] = ((CAy * xc) + (ACx * yc)) / ((CAy * -CBx) + (ACx *  BCy));
        hit.A[2] = 1.0f - hit.A[0] - hit.A[1];
    }
    return hit;
}
