#include "contextwindow.h"
#include "ui_contextwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>

ContextWindow::ContextWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContextWindow)
{
    ui->setupUi(this);
    img = QImage(this->contentsRect().width(),this->contentsRect().height(),QImage::Format_ARGB32);
    QString filename = QFileDialog::getOpenFileName(this,"Open scene", ".", "Wavefront OBJ (*.obj)");
    meshes = Mesh::fromFile(filename);
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
    Camera camera(float3(0.0f,0.0f,1.0f), float3(0.0f,0.0f,-0.5f), float3(0.0f,1.0f,0.0f), 30.0f, 1.0f, 2.0f);

    //    meshes[1].Tv += float3(0.0f,0.0f,0.0f);
//        meshes[1].Rv += float3(0.0f,10.0f,0.0f);
    //    meshes[1].Sv = float4(1.0f,1.0f,1.0f);

    rasterizer(buffers[0], meshes, camera);
    int halfW = img.width()  * 0.5f;
    int halfH = img.height() * 0.5f;
    if(debug)
    {
        for(int x = 0; x < halfW; x++)
            for(int y = 0; y < halfH; y++)
            {
                img.setPixelColor(halfW-x-1,       y,       QColor(toColor(buffers[0].color         [x*2+y*2*img.width()])));
                img.setPixelColor(halfW-x-1,       halfH+y, QColor(toColor(buffers[0].depth         [x*2+y*2*img.width()])));
                img.setPixelColor(img.width()-x-1, y,       QColor(normalToColor(buffers[0].normal  [x*2+y*2*img.width()])));
                img.setPixelColor(img.width()-x-1, halfH+y, QColor(toColor(buffers[0].position[x*2+y*2*img.width()]*2.0f)));
            }
    }
    else
    {
        for(int x = 0; x < img.width(); x++)
            for(int y = 0; y < img.height(); y++)
            {
                img.setPixelColor(img.width()-x-1, y, QColor(toColor(buffers[0].final[x+y*img.width()])));

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
    }
}
