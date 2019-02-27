#include "MarkDownTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarkDownTest w;
    w.showMaximized();
    return a.exec();
}
