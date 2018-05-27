#include "material.h"

#include <QDir>
#include <QFile>
#include <QtDebug>
#include <QtMath>

Material::Material()
{

}

QPair<QMap<QString, int>, QVector<Material>> Material::fromFile(QString filename)
{
    QFile file(filename);
    QFileInfo fileInfo(file);

    QMap<QString, int> materialsDictionary;

    QVector<Material> materials;

    if(!file.exists())
    {
        qCritical() << "File" << filename << "missing!";
        return QPair<QMap<QString, int>, QVector<Material>>(materialsDictionary, materials);
    }
    qInfo() << "Opening material file" << filename;


    if (file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();

            QStringList words = line.split(' ', QString::SkipEmptyParts);

            if(!words.empty())
            {
                QString first = words[0];

                qDebug() << first;

                if(first == "newmtl")
                {
                    materialsDictionary[words[1]] = materials.size();
                    materials.push_back(Material());
                }
                else if(first == "\tKa") //ambient color
                {
                    float4 color = float4(words[1].toFloat(), words[2].toFloat(), words[3].toFloat(), 1.0f);
                    materials.last().ambientColor = color;
                }
                else if(first == "\tKd") //diffuse color
                {
                    float4 color = float4(words[1].toFloat(), words[2].toFloat(), words[3].toFloat(), 1.0f);
                    materials.last().diffuseColor = color;
                }
                else if(first == "\tKs") //specular color
                {
                    float4 color = float4(words[1].toFloat(), words[2].toFloat(), words[3].toFloat(), 1.0f);
                    materials.last().specularColor = color;
                }
                else if(first == "\tNs") //specular exponent
                {
                    float color = words[1].toFloat();
                    materials.last().exponentColor = color;
                }
                else if(first == "\tmap_Ka") // ambient texture
                {
                    QString image = words[1].remove(words[1].length()-2,2);
                    materials.last().ambientTexture = new QImage(image);
                }
                else if(first == "\tmap_Kd") // diffuse texture
                {
                    QString image = words[1].remove(words[1].length()-2,2);
                    qDebug() << image;
                    materials.last().diffuseTexture = new QImage(image);
                }
                else if(first == "\tmap_Ks") // specular texture
                {
                    QString image = words[1].remove(words[1].length()-2,2);
                    materials.last().specularTexture = new QImage(image);
                }
                else if(first == "\tmap_Ns") // exponent texture
                {
                    QString image = words[1].remove(words[1].length()-2,2);
                    materials.last().exponentTexture = new QImage(image);
                }
                else if(first == "#") // exponent texture
                {
                    words.pop_front();
                    QString ba = words.join(' ');
                    ba = ba.remove(ba.length()-2,2);
                    qInfo() << ba;
                }
            }
        }
    }
    return QPair<QMap<QString, int>, QVector<Material>>(materialsDictionary, materials);
}

float4 sample2DTexture(float u, float v, QImage *image)
{
    if(image != nullptr)
    {
        if(!image->isNull())
        {
            double s = u - qFloor(u);
            double t = v - qFloor(v);

            int x = s * (image->width()-1);
            int y = (1.0f-t) * (image->height()-1);

            if(x>=0 && y>=0)
            {
//                if(s < 0.25 && t < 0.25)
//                {
//                    return float4(1.0f, 1.0f, 1.0f, 1.0f);
//                }
                QColor c = image->pixelColor(x,y);
                return float4(c.redF(), c.greenF(), c.blueF(), 1.0f);
            }
            else
                return float4(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    return float4(1.0f,1.0f,1.0f,1.0f);
}
