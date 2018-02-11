#include "contextwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContextWindow w;
    w.show();
    w.render();

    return a.exec();
}
