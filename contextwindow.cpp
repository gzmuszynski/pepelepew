#include "contextwindow.h"
#include "ui_contextwindow.h"
#include <QDebug>

ContextWindow::ContextWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContextWindow)
{
    ui->setupUi(this);
    img = QImage(this->contentsRect().width(),this->contentsRect().height(),QImage::Format_ARGB32);
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
    QVector<Mesh> meshes;
    Camera camera(float4(0.0f,0.0f,-1.0f), float4(0.0f,0.0f,0.0f), float4(0.0f,1.0f,0.0f), 45.0f, 0.1f, 2.0f);

    rasterizer(buffers[0], meshes, camera);
    for(int x = 0; x < img.width(); x++)
        for(int y = 0; y < img.height(); y++)
            //                img.setPixelColor(x,y,QColor(buffers[0].color[x+y*img.width()]));
            img.setPixelColor(x,y,QColor(qrand()%256,qrand()%256,qrand()%256));
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
    painter.drawLine(0,0,qrand()%500,qrand()%500);
    if(!img.isNull())
        painter.drawImage(0,0,img);
    painterReady = true;
}
