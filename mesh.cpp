#include "mesh.h"

#include <QFile>
#include <stdio.h>
#include <iterator>
#include <QMap>
#include <QtDebug>
#include <QFileInfo>

Mesh::Mesh() : Tv(0.0f), Rv(0.0f), Sv(1.0f)
{

}
Mesh::Mesh(const Mesh &orig) : Tv(orig.Tv), Rv(orig.Rv), Sv(orig.Sv), verts(orig.verts), tris(orig.tris)
{

}

QPair<QVector<Mesh>, QVector<Material>> Mesh::fromFile(QString filename)
{
    // TO-DO

    QFile file(filename);
    QFileInfo fileInfo(file);

    if(!file.exists())
    {
        qCritical() << "File" << filename << "missing!";
        return QPair<QVector<Mesh>, QVector<Material>>(QVector<Mesh>(0),QVector<Material>(0));
    }
    qInfo() << "Opening" << filename;

    QMap<QString, int> materialsDictionary;
    QVector<Material> materials;
    int mat = 0;

    QVector<Mesh> meshes(0);

    QVector<float3> poses(1);
    QVector<float3> normals(1);
    QVector<float3> coords(1);

    if (file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();

            QStringList words = line.split(' ', QString::SkipEmptyParts);

            if(!words.empty())
            {
                QString first = words[0];

                if(first == "mtllib")
                {
                    QPair<QMap<QString, int>, QVector<Material>> mtllib = Material::fromFile(fileInfo.path()+'/'+words[1].remove(words[1].length()-2,2));
                    materialsDictionary.unite(mtllib.first);
                    materials.append(mtllib.second);
                }
                if(first == "usemtl")
                {
                    mat = materialsDictionary[words[1]];
                }
                if(first == "g")
                {
                    meshes.push_back(Mesh());
                }
                if(first == "v")
                {
                    float3 pos(words[1].toFloat(),
                               words[2].toFloat(),
                               words[3].toFloat());

                    poses.push_back(pos);
                }
                else if(first == "vn")
                {
                    float3 normal(words[1].toFloat(),
                            words[2].toFloat(),
                            words[3].toFloat());

                    normals.push_back(normal);
                }
                else if(first == "vt")
                {
                    float3 coord(words[1].toFloat(),
                            words[2].toFloat(),
                            words[3].toFloat());

                    coords.push_back(coord);
                }
                else if(first == "f")
                {
                    QStringList v1 = words[1].split('/', QString::KeepEmptyParts);
                    QStringList v2 = words[2].split('/', QString::KeepEmptyParts);
                    QStringList v3 = words[3].split('/', QString::KeepEmptyParts);

                    int4 pos{v1[0].toInt(),
                             v2[0].toInt(),
                             v3[0].toInt()};

                    int4 verts{meshes.last().verts.size(),
                               meshes.last().verts.size()+1,
                               meshes.last().verts.size()+2, mat};

                    meshes.last().verts.push_back(Vertex(poses[pos.a], normals[v1[2].toInt()], coords[v1[1].toInt()]));
                    meshes.last().verts.push_back(Vertex(poses[pos.b], normals[v2[2].toInt()], coords[v2[1].toInt()]));
                    meshes.last().verts.push_back(Vertex(poses[pos.c], normals[v3[2].toInt()], coords[v3[1].toInt()]));

                    meshes.last().tris.push_back(verts);
                }
                else if(first == "#")
                {
                    words.pop_front();
                    QString ba = words.join(' ');
                    ba = ba.remove(ba.length()-2,2);
                    qInfo() << ba;
                }
            }
        }
    }
    return QPair<QVector<Mesh>, QVector<Material>>(meshes, materials);
}
