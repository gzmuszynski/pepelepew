#ifndef CONTEXTWINDOW_H
#define CONTEXTWINDOW_H

#include "buffer.h"
#include "rasterizer.h"

#include <QGraphicsView>

namespace Ui {
class ContextWindow;
}

class ContextWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ContextWindow(QWidget *parent = 0);
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
    Rasterizer rasterizer;
    QImage img;
    bool painterReady;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CONTEXTWINDOW_H
