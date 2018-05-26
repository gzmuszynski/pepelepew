#ifndef MATERIAL_H
#define MATERIAL_H

#include <QImage>
#include <QVector>
#include "float4.h"



class Material
{
public:
    Material();

    static QPair<QMap<QString, int>, QVector<Material> > fromFile(QString filename);


    float4 ambientColor;
    float4 diffuseColor;
    float4 specularColor;
    float  exponentColor;

    QImage* ambientTexture  = nullptr;
    QImage* diffuseTexture  = nullptr;
    QImage* specularTexture = nullptr;
    QImage* exponentTexture = nullptr;

};

float4 sample2DTexture(float u, float v, QImage* image);

#endif // MATERIAL_H
