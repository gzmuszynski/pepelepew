#ifndef MAT4_H
#define MAT4_H
#include <float4.h>
#include <QtMath>

static float rad = M_PI / 180.0f;

struct mat4
{
    float4 W[4];

    mat4(float num = 1.0f);
    mat4(const mat4 &mat);
    mat4(float4 &W0, float4 &W1, float4 &W2, float4 &W3);

    float4 & operator [](int i);
    
    mat4 operator * (mat4 &B);
    mat4 operator *=(mat4 &A);
};

float4 operator *(float4 &vec, mat4 &mat);
float4 operator *(mat4 &mat, float4 &vec);

float4 operator *=(float4 &vec, mat4 &mat);

mat4 inverse(mat4 &mat);
mat4 transpose(mat4 &mat);

#endif // MAT4_H
