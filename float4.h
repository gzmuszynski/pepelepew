#include <glm/glm.hpp>
#include <QColor>

typedef glm::vec3 float3;
typedef glm::vec4 float4;

//QColor toColor(float4 &n);
QColor toColor(float4 n);
float4 fromColor(QColor color);

QColor normalToColor(float4 &n);
