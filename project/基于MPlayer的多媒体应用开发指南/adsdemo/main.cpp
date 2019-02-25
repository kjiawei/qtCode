#include <QtGui/QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include "mainwidget.h"

/*
void customMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;

    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
        break;

    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;

    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }

    QFile outFile("/tmp/debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qInstallMsgHandler(customMessageHandler);

    MainWidget w;
    w.showFullScreen();

    return a.exec();
}
