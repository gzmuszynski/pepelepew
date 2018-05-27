#include "contextwindow.h"
#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    float fov = 150.0f;
    bool useMRT = false;
    int param1, param2 = 0;

    qDebug() << argc;
    if(argc>1)
        fov = atof(argv[1]);
    if(argc>2)
        useMRT = (bool)atoi(argv[2]);
    if(argc>3)
        param1 = atoi(argv[3]);
    if(argc>4)
        param2 = atoi(argv[4]);


    ContextWindow w(0,fov,useMRT,param1,param2);
    w.show();


    w.render();

    return a.exec();
}
