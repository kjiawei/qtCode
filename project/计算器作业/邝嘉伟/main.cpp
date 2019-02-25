#include "calcqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcQt w;
    w.show();

    return a.exec();
}
