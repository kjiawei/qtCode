#include "downlistwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DownListWin w;
    w.show();

    return a.exec();
}
