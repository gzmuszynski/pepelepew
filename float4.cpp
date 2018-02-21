#include "float4.h"
#include <QColor>
#include <QtMath>


QColor toColor(float4 &n)
{
    int _x = qBound(0, qFloor(n.w*n.x * 255.0f), 255);
    int _y = qBound(0, qFloor(n.w*n.y * 255.0f), 255);
    int _z = qBound(0, qFloor(n.w*n.z * 255.0f), 255);

    return QColor(_x, _y, _z, 255);
}
QColor normalToColor(float4 &n)
{
    return toColor(float4(n.w*(n.x*0.5f+0.5f), n.w*(n.y*0.5f+0.5f), n.w*(n.z*0.5f+0.5f), n.w));
}
