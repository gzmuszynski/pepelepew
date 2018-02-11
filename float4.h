#ifndef FLOAT4_H
#define FLOAT4_H
#include <xmmintrin.h>
#include <QColor>

class float4
{
public:
    float4(float x, float y, float z, float w);
    float4(float x, float y, float z);
    float4(const float4 &o);
    float4(float xyz = 0.0f);

    float4 operator -();

    float4 operator *(float4 o);
    float4 operator +(float4 o);
    float4 operator -(float4 o);
    float4 operator /(float4 o);

    float4 operator *=(float4 o);
    float4 operator +=(float4 o);
    float4 operator -=(float4 o);
    float4 operator /=(float4 o);

    float & operator [](int i);

    float length();
    float length2();

    float4 normalize();

    float x, y, z, w;

    operator QColor();
};

float4 operator * (float &a, float4 &o);
float4 operator + (float &a, float4 &o);

float4 operator * (float4 &o, float &a);
float4 operator + (float4 &o, float &a);
float4 operator - (float4 &o, float &a);
float4 operator / (float4 &o, float &a);

float4 operator *=(float4 &o, float &a);
float4 operator +=(float4 &o, float &a);
float4 operator -=(float4 &o, float &a);
float4 operator /=(float4 &o, float &a);

float  dotProduct  (float4 &o1, float4 &o2);
float4 crossProduct(float4 &o1, float4 &o2);
float4 normalize(float4 &o);

#endif // FLOAT4_H
