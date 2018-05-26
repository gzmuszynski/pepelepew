#include "float4.h"
#include <QColor>
#include <QtMath>


//QColor toColor(float4 &n)
//{
//    int _x = glm::clamp(glm::floor(n.w*n.x * 255.0f),0.0f ,  255.0f);
//    int _y = glm::clamp(glm::floor(n.w*n.y * 255.0f),0.0f ,  255.0f);
//    int _z = glm::clamp(glm::floor(n.w*n.z * 255.0f),0.0f ,  255.0f);

//    return QColor(_x, _y, _z, 255);
//}
QColor toColor(float4 n)
{
    int _x = glm::clamp(glm::floor(n.w*n.x * 255.0f),0.0f ,  255.0f);
    int _y = glm::clamp(glm::floor(n.w*n.y * 255.0f),0.0f ,  255.0f);
    int _z = glm::clamp(glm::floor(n.w*n.z * 255.0f),0.0f ,  255.0f);

    return QColor(_x, _y, _z, 255);
}
QColor normalToColor(float4 &n)
{
    float4 tmp = float4(n.w*(n.x*0.5f+0.5f), n.w*(n.y*0.5f+0.5f), n.w*(n.z*0.5f+0.5f), n.w);
    return toColor(tmp);
}

float4 fromColor(QColor color)
{
    return float4(color.red(), color.green(), color.blue(), color.alpha());
}
