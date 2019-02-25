#include "qqqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qqQT w;
    w.show();

    return a.exec();
}
