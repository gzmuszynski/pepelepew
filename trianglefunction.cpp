#include "trianglefunction.h"


TriangleFunction::TriangleFunction()
{

}

Hit TriangleFunction::operator()(Vertex* &V, float x, float y)
{
    Hit hit;

    float ABy = V[0].pos.y - V[1].pos.y;
    float ABx = V[0].pos.x - V[1].pos.x;
    float BCy = V[1].pos.y - V[2].pos.y;
    float CBx = V[2].pos.x - V[1].pos.x;
    float ACx = V[0].pos.x - V[2].pos.x;
    float CAy = V[2].pos.y - V[0].pos.y;

    float xc =  x - V[2].pos.x;
    float yc =  y - V[2].pos.y;

    float AB =  ABx * (y - V[0].pos.y) - ABy * (x - V[0].pos.x);
    float BC = -CBx * (y - V[1].pos.y) - BCy * (x - V[1].pos.x);
    float CA = -ACx * yc - CAy * xc;

    hit.test = ((AB <= 0.0f || (AB == 0.0f && (ABy < 0.0f || (ABy == 0.0f && ABx < 0.0f)))) &&
                (BC <= 0.0f || (BC == 0.0f && (BCy < 0.0f || (BCy == 0.0f && CBx > 0.0f)))) &&
                (CA <= 0.0f || (CA == 0.0f && (CAy < 0.0f || (CAy == 0.0f && ACx > 0.0f)))) );

    if( hit.test )
    {
        hit.A[0] = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx) + (CBx * -CAy));
        hit.A[1] = ((CAy * xc) + (ACx * yc)) / ((CAy * -CBx) + (ACx *  BCy));
        hit.A[2] = 1.0f - hit.A[0] - hit.A[1];
    }
    return hit;
}
