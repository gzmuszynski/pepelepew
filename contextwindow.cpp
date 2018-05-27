#include "contextwindow.h"
#include "ui_contextwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTime>

ContextWindow::ContextWindow(QWidget *parent, float fov, bool useMRT, int param1, int param2) :
    QWidget(parent),
    ui(new Ui::ContextWindow),
    fov(fov)
{
    if(useMRT)
    {
        rasterizer = new MRTRasterizer(param1, param2);
    }
    else
    {
        rasterizer = new Rasterizer(param1, param2);
    }
    ui->setupUi(this);
    img = QImage(this->contentsRect().width(),this->contentsRect().height(),QImage::Format_ARGB32);
    QString filename = QFileDialog::getOpenFileName(this,"Open scene", ".", "Wavefront OBJ (*.obj)");
    QPair<QVector<Mesh>, QVector<Material>> obj = Mesh::fromFile(filename);
    meshes = obj.first;
    materials = obj.second;
    lights.push_back(Light(float4(0.0f,0.0f,0.0f,1.0f)));
    lights[0].ambient = float3(1.0f,1.0f,1.0f);
    lights[0].diffuse = float3(0.0f,0.0f,0.0f);
    lights[0].specular = float3(0.0f,0.0f,0.0f);
}

ContextWindow::~ContextWindow()
{
    delete ui;
}

void ContextWindow::render()
{
    int width  = contentsRect().width();
    int height = contentsRect().height();


    buffers.push_back(Buffer(width, height));
    buffers[0].clear();
}

void ContextWindow::drawNextFrame()
{
    painterReady = false;
    Camera camera(float3(0.0f,0.0f,0.0f), float3(0.0f,1.0f,0.0f), float3(0.0f,0.0f,1.0f), fov, 0.5f, 5.0f);

    //    meshes[1].Tv += float3(0.0f,0.0f,0.0f);
//        meshes[1].Rv += float3(0.0f,10.0f,0.0f);
    //    meshes[1].Sv = float4(1.0f,1.0f,1.0f);

    QTime before = QTime::currentTime();
    rasterizer->operator ()(buffers[0], meshes, camera, materials, lights);
    int elapsed = before.msecsTo(QTime::currentTime());

    qDebug() << QString("Frame time: %1ms").arg(elapsed);
    int halfW = img.width()  * 0.5f;
    int halfH = img.height() * 0.5f;
    if(debug)
    {
        for(int x = 0; x < halfW; x++)
            for(int y = 0; y < halfH; y++)
            {
                img.setPixelColor(x,       halfH -y-1,       QColor(toColor(buffers[0].color         [x*2+y*2*img.width()])));
                img.setPixelColor(x,       img.height()-y-1, QColor(toColor(buffers[0].depth         [x*2+y*2*img.width()])));
                img.setPixelColor(halfW+x, halfH-y-1,       QColor(normalToColor(buffers[0].normal  [x*2+y*2*img.width()])));
                img.setPixelColor(halfW+x, img.height()-y-1, QColor(toColor(buffers[0].position      [x*2+y*2*img.width()])));
            }
    }
    else
    {
        for(int x = 0; x < img.width(); x++)
            for(int y = 0; y < img.height(); y++)
            {
                img.setPixelColor(x, img.height()-y-1, QColor(toColor(buffers[0].final[x+y*img.width()])));

                //            img.setPixelColor(x,y,QColor(qrand()%256,qrand()%256,qrand()%256));
            }
    }
    repaint();
}


void ContextWindow::mousePressEvent(QMouseEvent *event)
{
    if(painterReady)
        drawNextFrame();
}


void ContextWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //    painter.drawLine(0,0,qrand()%500,qrand()%500);
    if(!img.isNull())
        painter.drawImage(0,0,img);
    painterReady = true;
}


void ContextWindow::resizeEvent(QResizeEvent *event)
{
    buffers.clear();

    render();

    img = img.scaled(contentsRect().width(), contentsRect().height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    repaint();

}


void ContextWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space: { debug = !debug; drawNextFrame(); break;}
    case Qt::Key_S:
    {
        QString filename = QFileDialog::getSaveFileName(this, "Zapisz obraz", NULL, "Portable Network Graphics (*.png)");
        if(!filename.isNull())
        {
            img.save(filename);
        }
    }
    }
}
