#ifndef CONTEXTWINDOW_H
#define CONTEXTWINDOW_H

#include "buffer.h"
#include "light.h"
#include "mrtrasterizer.h"
#include "rasterizer.h"

#include <QGraphicsView>

namespace Ui {
class ContextWindow;
}

class ContextWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ContextWindow(QWidget *parent = 0, float fov = 150.0f, bool useMRT = false, int param1 = 0, int param2 = 0);
    ~ContextWindow();
    void render();

signals:
    void frameReady();
public slots:
    void drawNextFrame();
private:
    Ui::ContextWindow *ui;
    QPainter *painter;
    QList<Buffer> buffers;
    Rasterizer *rasterizer;
    QImage img;
    bool painterReady;
    QVector<Mesh> meshes;
    QVector<Material> materials;
    QVector<Light> lights;
    // QWidget interface

    float fov;
    bool debug = true;
protected:
    void mousePressEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CONTEXTWINDOW_H
