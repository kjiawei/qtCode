#include "cutscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CutScreen w;
    w.show();

    return a.exec();
}
