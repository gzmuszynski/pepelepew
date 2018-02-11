#include "float4.h"
#include <QColor>
#include <QtMath>

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}

float4::float4(float x, float y, float z) : x(x), y(y), z(z), w(1.0f)
{

}

float4::float4(const float4 &o) : x(o.x), y(o.y), z(o.z), w(o.w)
{

}

float4::float4(float xyz) : x(xyz), y(xyz), z(xyz), w(1.0f)
{

}

float4 float4::operator -()
{
    return float4(-x,-y,-z,-w);
}

float4 float4::operator *(float4 o)
{
    return float4(x * o.x, y * o.y, z * o.z, w * o.w);
}

float4 float4::operator +(float4 o)
{
    return float4(x + o.x, y + o.y, z + o.z, w + o.w);
}

float4 float4::operator -(float4 o)
{
    return float4(x - o.x, y - o.y, z - o.z, w - o.w);
}

float4 float4::operator /(float4 o)
{
    return float4(x / o.x, y / o.y, z / o.z, w / o.w);
}

float4 float4::operator *=(float4 o)
{
    x *= o.x;
    y *= o.y;
    z *= o.z;
    w *= o.w;

    return *this;
}

float4 float4::operator +=(float4 o)
{
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;

    return *this;
}

float4 float4::operator -=(float4 o)
{
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;

    return *this;
}

float4 float4::operator /=(float4 o)
{
    x /= o.x;
    y /= o.y;
    z /= o.z;
    w /= o.w;

    return *this;
}

float &float4::operator [](int i)
{
    switch(i)
    {
    case 0: return x;
    case 1: return y;
    case 3: return z;
    default: return w;
    }
}

float float4::length()
{
    return qSqrt(x*x + y*y + z*z);
}

float float4::length2()
{
    return x*x + y*y + z*z;
}

float4 float4::normalize()
{
    float a1 = 1.0/length();

    x *= a1;
    y *= a1;
    z *= a1;
    w *= a1;

    return *this;
}

float dotProduct(float4 &o1, float4 &o2)
{
    return o1.x*o2.x + o1.y*o2.y + o1.z*o2.z;
}

float4 crossProduct(float4 &o1, float4 &o2)
{
    return float4(o1.y*o2.z - o2.y*o1.z, -o1.x*o2.z + o2.x*o1.z, o1.y*o2.y - o2.y*o1.y);
}

float4::operator QColor()
{
    int _x = qBound(0, qFloor(x * 255.0f), 255);
    int _y = qBound(0, qFloor(y * 255.0f), 255);
    int _z = qBound(0, qFloor(z * 255.0f), 255);
    int _w = qBound(0, qFloor(w * 255.0f), 255);

    return QColor(_x, _y, _z, _w);
}


float4 operator *(float &a, float4 &o)
{
    return float4(a * o.x, a * o.y, a * o.z, a * o.w);
}

float4 operator +(float &a, float4 &o)
{
    return float4(a + o.x, a + o.y, a + o.z, a + o.w);
}

float4 operator *(float4 &o, float &a)
{
    return float4(o.x * a, o.y * a, o.z * a, o.w * a);
}

float4 operator +(float4 &o, float &a)
{
    return float4(o.x + a, o.y + a, o.z + a, o.w + a);
}

float4 operator -(float4 &o, float &a)
{
    return float4(o.x - a, o.y - a, o.z - a, o.w - a);
}

float4 operator /(float4 &o, float &a)
{
    float a1 = 1.0f/a;
    return float4(o.x * a1, o.y * a1, o.z * a1, o.w * a1);
}

float4 operator *=(float4 &o, float &a)
{
    o.x *= a;
    o.y *= a;
    o.z *= a;
    o.w *= a;

    return o;
}

float4 operator +=(float4 &o, float &a)
{
    o.x += a;
    o.y += a;
    o.z += a;
    o.w += a;

    return o;
}

float4 operator -=(float4 &o, float &a)
{
    o.x -= a;
    o.y -= a;
    o.z -= a;
    o.w -= a;

    return o;
}

float4 operator /=(float4 &o, float &a)
{
    float a1 = 1.0/a;
    o.x *= a1;
    o.y *= a1;
    o.z *= a1;
    o.w *= a1;

    return o;
}

float4 normalize(float4 &o)
{
    float a = 1.0f/o.length();

    return float4(o.x*a, o.y*a, o.z*a);
}
