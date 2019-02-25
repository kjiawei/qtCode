/*******************************************
*main.cpp
*
*项目名称：mp3播放器
*开发团队：QP1301_
*开发时间：2013.7.31——2013.8.04
********************************************
*/

#include <QApplication>
#include "player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    player obj;
    obj.show();
    return app.exec();
}
