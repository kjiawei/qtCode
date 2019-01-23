#ifndef _COMMONUI_H_
#define _COMMONUI_H_

//控件布局类 用宏函数绘制UI 注意命名规范

#include <QtGui>
#include <QWidget>

/*------------------------ BPM ---------------------------*/
#define SCENE_BPM_CREATE_T(x, pos_x, pos_y, pos_w)             \
    x.setGeometry(QRect(pos_x, SCENE_SETUP_ROW_##pos_y,        \
                        pos_w, SCENE_SETUP_WIDGET_HIGH));      \
    x.setAlignment(Qt::AlignVCenter | Qt::AlignRight);         \
    x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    x.setStyleSheet(CONFIG_COLOR_LABEL)

#define SCENE_BPM_CREATE_L(x, pos_x, pos_y)                                         \
    x.setGeometry(QRect(pos_x, SCENE_SETUP_ROW_##pos_y,                             \
                        SCENE_SETUP_COL_WIDTH_EDIT - 30, SCENE_SETUP_WIDGET_HIGH)); \
    x.setFont(QFont(QString(CONFIG_FONT_STYLE),                                     \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL));                      \
    x.setAlignment(Qt::AlignVCenter | Qt::AlignCenter);                             \
    LINEEDIT_STYLE(x)

#define SCENE_BPM_CREATE_U(x, pos_x, pos_y, pos_w)             \
    x.setGeometry(QRect(pos_x, SCENE_SETUP_ROW_##pos_y,        \
                        pos_w, SCENE_SETUP_WIDGET_HIGH));      \
    x.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);          \
    x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    x.setStyleSheet(CONFIG_COLOR_LABEL)

#define SCENE_BPM_CREATE_TABLE(x, y)                               \
    do                                                             \
    {                                                              \
        x.setGeometry(QRect(460, SCENE_SETUP_ROW_##y,              \
                            150, SCENE_SETUP_WIDGET_HIGH));        \
        ;                                                          \
        x.setAlignment(Qt::AlignVCenter | Qt::AlignRight);         \
        x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        x.setStyleSheet(CONFIG_COLOR_LABEL);                       \
    } while (0)

#define SCENE_BPM_CREATE_LABLE(x, pos_x, y)                        \
    do                                                             \
    {                                                              \
        x.setGeometry(QRect(pos_x, SCENE_SETUP_ROW_##y,            \
                            150, SCENE_SETUP_WIDGET_HIGH));        \
        ;                                                          \
        x.setAlignment(Qt::AlignVCenter | Qt::AlignRight);         \
        x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        x.setStyleSheet(CONFIG_COLOR_LABEL);                       \
    } while (0)

#define SCENE_BPM_CREATE_LINEEDIT(x, y)                            \
    do                                                             \
    {                                                              \
        x.setGeometry(QRect(620, SCENE_SETUP_ROW_##y,              \
                            SCENE_SETUP_COL_WIDTH_EDIT,            \
                            SCENE_SETUP_WIDGET_HIGH));             \
        x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        x.setAlignment(Qt::AlignVCenter | Qt::AlignCenter);        \
        LINEEDIT_STYLE(x);                                         \
    } while (0)

#define SCENE_BPM_CREATE_UNIT(x, y)                                \
    do                                                             \
    {                                                              \
        x.setGeometry(QRect(745, SCENE_SETUP_ROW_##y,              \
                            60, SCENE_SETUP_WIDGET_HIGH));         \
        x.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);          \
        x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        x.setStyleSheet(CONFIG_COLOR_LABEL);                       \
    } while (0)

#define SCENE_BPM_CREATE_SYM(x, pos_x, pos_y, pos_w)           \
    x.setGeometry(QRect(pos_x, pos_y,                          \
                        pos_w, SCENE_SETUP_WIDGET_HIGH));      \
    x.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);          \
    x.setFont(QFont(QString(CONFIG_FONT_STYLE),                \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    x.setStyleSheet(CONFIG_COLOR_LABEL)

#define SCENE_BPM_SETUP_CREATE_SHOWSTYLE(x, pos_x, pos_y)                      \
    do                                                                         \
    {                                                                          \
        SCENE_SETUP_WIDGET_XYW((x), pos_x, pos_y, SCENE_SETUP_COL_WIDTH_EDIT); \
        LINEEDIT_SHOWSTYLE(x);                                                 \
    } while (0)

/*------------------widgetCommon------------------------*/
#define LINEEDIT_STYLE(x)                       \
    (x).setStyleSheet(                            \
            "QLineEdit {"                       \
            "color:#cdcdcd;"                    \
            "border: 1px groove #0f131b;"       \
            "border-radius: 9px;"               \
            "padding: 0 8px;"                   \
            "background: #123f75;"              \
            "}");                               \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), \
            CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (x).setAlignment(Qt::AlignCenter)

#define LINEEDIT_SHOWSTYLE(x)                       \
    (x).setStyleSheet(                            \
            "QLineEdit {"                       \
            "color:#000000;"                    \
            "border: 1px groove #0f131b;"       \
            "border-radius: 9px;"               \
            "padding: 0 8px;"                   \
            "background: #acacac;"              \
            "}");                                \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), \
            CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (x).setAlignment(Qt::AlignCenter)

#define LINENOEDIT_STYLE(x)                       \
    (x).setStyleSheet(                            \
            "QLineEdit {"                       \
            "color:#cdcdcd;"                    \
            "border-style:none;"                \
            "padding: 0 8px;"                   \
            "background-color:transparent;"              \
            "}");                               \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), \
            CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (x).setAlignment(Qt::AlignCenter)


#define COMBOBOX_STYLE(x)                       \
    (x).setStyleSheet("QComboBox {"               \
                "color:#cdcdcd;"                \
                "border-radius: 9px;"           \
                "background: #123f75;"          \
                "padding: 0 8px;"               \
                "}")

#define RADIOBUTTON_STYLE(x)                    \
    (x).setStyleSheet("QRadioButton {color:#dce6f0;}"     \
            "QRadioButton::indicator {width: 29px;height: 31px;} "  \
            "QRadioButton::indicator::checked {image: url(:/resource/images/radio_button_check.png);} "  \
            "QRadioButton::indicator::unchecked {image: url(:/resource/images/radio_button_uncheck.png);}")

#define LABEL_TITLE_STYLE(x)                    \
    (x).setAlignment(Qt::AlignVCenter | Qt::AlignLeft);       \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), \
                CFG_FONT_SIZE_TITLE, CONFIG_FONT_NORMAL));  \
    (x).setStyleSheet(CONFIG_COLOR_WHITE_CHARS)

#define LABEL_REMIND_TITLE(x)                    \
    (x).setAlignment(Qt::AlignVCenter | Qt::AlignRight);      \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE),             \
                CFG_FONT_SIZE_FOURTH, CONFIG_FONT_NORMAL)); \
    (x).setStyleSheet(CONFIG_COLOR_WHITE_CHARS)

#define LABEL_REMIND_VALUE(x)                    \
    (x).setAlignment(Qt::AlignVCenter | Qt::AlignCenter);       \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE),             \
                CFG_FONT_SIZE_FOURTH, CONFIG_FONT_NORMAL)); \
    (x).setStyleSheet(CONFIG_COLOR_WHITE_CHARS)

#define LABEL_REMIND_UNIT(x)                    \
    (x).setAlignment(Qt::AlignVCenter | Qt::AlignLeft);       \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE),             \
                CFG_FONT_SIZE_FOURTH, CONFIG_FONT_NORMAL)); \
    (x).setStyleSheet(CONFIG_COLOR_WHITE_CHARS)

/*
#define BUTTON_SIMPLE_STYLE(x)                    \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), 15));   \
    connect(&x, SIGNAL(clicked()), audio, SLOT(beep()),)
    //x.setStyleSheet(CONFIG_COLOR_BLUE_CHARS)

*/

#define BUTTON_SIMPLE_STYLE(x)                    \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE), 15))

/*
#define MESSAGE_PROMPT_BOX(title,text)    \
       QMessageBox::information(0,title,text,QMessageBox::Ok)
*/

#define MESSAGE_PROMPT_BOX(title,text)     \
    QMessageBox informat(QMessageBox::Information,title,text,QMessageBox::Yes);\
    informat.setWindowFlags(Qt::Widget); \
    informat.setWindowFlags(Qt::FramelessWindowHint);\
    informat.move(300,300);  \
    informat.exec();

//工程设置界面专用提示框
#define MESSAGE_ENGINEER_PROMPT_BOX(title,text)     \
    QMessageBox informat(QMessageBox::Information,title,text,QMessageBox::Yes);\
    informat.setWindowFlags(Qt::Widget); \
    informat.setStyleSheet("background-color:yellow");\
    informat.move(450,300);  \
    informat.exec();

/*-----------------全局/setup界面-----------------------*/
/* Style: label. lineedit. label(unit). */
#define SCENE_SETUP_COL_LABEL                   90   //标签列X坐标
#define SCENE_SETUP_COL_LINEEDIT                395  //编辑框列X坐标
#define SCENE_SETUP_COL_UNIT                    510  //列的X坐标
#define SCENE_SETUP_COL_WIDTH_LABEL             300  //标签列X坐标
#define SCENE_SETUP_COL_WIDTH_EDIT              110  //标签列X坐标
#define SCENE_SETUP_COL_WIDTH_COMBOBOX          110  //标签列X坐标
#define SCENE_SETUP_COL_WIDTH_UNIT              100  //标签列X坐标
#define SCENE_SETUP_WIDGET_HIGH                 38  //标签列X坐标
#define SCENE_SETUP_COL_WIDTH_PARAMS_LABEL      110  //标签列X坐标
#define SCENE_SETUP_COL_WIDTH_PARAMS_EDIT       95//标签列X坐标
#define SCENE_SETUP_PARAMS_TITLE_COL_1          150//标签列X坐标
#define SCENE_SETUP_PARAMS_TITLE_COL_2          355//标签列X坐标
#define SCENE_SETUP_PARAMS_TITLE_COL_3          555//标签列X坐标
#define SCENE_SETUP_PARAMS_TITLE_COL_4          755//标签列X坐标
#define SCENE_SETUP_PARAMS_EDIT_COL_1           260//标签列X坐标
#define SCENE_SETUP_PARAMS_EDIT_COL_2           465//标签列X坐标
#define SCENE_SETUP_PARAMS_EDIT_COL_3           665//标签列X坐标
#define SCENE_SETUP_PARAMS_EDIT_COL_4           865//标签列X坐标
#define SCENE_SETUP_COL_UNIT_PARAMS_1           360//标签列X坐标
#define SCENE_SETUP_COL_UNIT_PARAMS_2           565//标签列X坐标
#define SCENE_SETUP_COL_UNIT_PARAMS_3           765//标签列X坐标
#define SCENE_SETUP_COL_UNIT_PARAMS_4           965//标签列X坐标

#define SCENE_SETUP_ROW_1                       76//标签列X坐标
#define SCENE_SETUP_ROW_2                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_1+7)
#define SCENE_SETUP_ROW_3                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_2+7)
#define SCENE_SETUP_ROW_4                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_3+7)
#define SCENE_SETUP_ROW_5                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_4+7)
#define SCENE_SETUP_ROW_6                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_5+7)
#define SCENE_SETUP_ROW_7                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_6+7)
#define SCENE_SETUP_ROW_8                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_7+7)
#define SCENE_SETUP_ROW_9                       (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_8+7)
#define SCENE_SETUP_ROW_10                      (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_9+7)
#define SCENE_SETUP_ROW_11                      (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_10+7)
#define SCENE_SETUP_ROW_12                      (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_11+7)
#define SCENE_SETUP_ROW_13                      (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_12+7)
#define SCENE_SETUP_ROW_14                      (SCENE_SETUP_WIDGET_HIGH+SCENE_SETUP_ROW_13+7)

//参数表 x代表控件 y代表行数(纵坐标) z代表列数(横坐标) (以下均同) 没被用过
#define SCENE_SETUP_CREATE_PARAMS_TABLE(x,y,z)           \
    do {                                        \
        (x).setGeometry(QRect(SCENE_SETUP_PARAMS_TITLE_COL_##z,          \
                    SCENE_SETUP_ROW_##y,                        \
                    SCENE_SETUP_COL_WIDTH_PARAMS_LABEL,         \
                    SCENE_SETUP_WIDGET_HIGH));;                 \
        (x).setAlignment( Qt::AlignVCenter | Qt::AlignRight); \
        (x).setFont(QFont(QString(CONFIG_FONT_STYLE),         \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        (x).setStyleSheet(CONFIG_COLOR_LABEL);                \
    } while(0)

//参数编辑框
#define SCENE_SETUP_CREATE_PARAMS_LINEEDIT(x,y,z)        \
    do {                                        \
        (x).setGeometry(QRect(SCENE_SETUP_PARAMS_EDIT_COL_##z, SCENE_SETUP_ROW_##y, SCENE_SETUP_COL_WIDTH_PARAMS_EDIT,  \
                SCENE_SETUP_WIDGET_HIGH));          \
        LINEEDIT_STYLE(x);                      \
    } while(0)

//参数单位
#define SCENE_SETUP_CREATE_PARAMS_UNIT(x,y,z)            \
        do {                                    \
            (x).setGeometry(QRect(SCENE_SETUP_COL_UNIT_PARAMS_##z,       \
                        SCENE_SETUP_ROW_##y,                \
                        SCENE_SETUP_COL_WIDTH_UNIT,         \
                        SCENE_SETUP_WIDGET_HIGH));          \
            (x).setAlignment( Qt::AlignVCenter | Qt::AlignLeft); \
            (x).setFont(QFont(QString(CONFIG_FONT_STYLE),     \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
            (x).setStyleSheet(CONFIG_COLOR_LABEL);    \
        } while(0)

//表格
/* Create a table, x:QLabel, y:1~7 */
#define SCENE_SETUP_CREATE_TABLE(x,y)           \
    do {                                        \
        (x).setGeometry(QRect(SCENE_SETUP_COL_LABEL,          \
                    SCENE_SETUP_ROW_##y,                        \
                    SCENE_SETUP_COL_WIDTH_LABEL,                \
                    SCENE_SETUP_WIDGET_HIGH));;                 \
        (x).setAlignment( Qt::AlignVCenter | Qt::AlignRight); \
    (x).setFont(QFont(QString(CONFIG_FONT_STYLE),         \
                CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        (x).setStyleSheet(CONFIG_COLOR_LABEL);                \
    } while(0)

//普通控件
/* Create a widget */
#define SCENE_SETUP_WIDGET_XYW(p, x, y, w)      \
    do {                                        \
        (p).setGeometry(QRect(x, SCENE_SETUP_ROW_##y, w,  \
                    SCENE_SETUP_WIDGET_HIGH));          \
    } while(0)

//控件
#define SCENE_SETUP_WIDGET(x,y,w)            \
    SCENE_SETUP_WIDGET_XYW((x), SCENE_SETUP_COL_LINEEDIT, y, w)

//编辑控件
/* Create a LineEdit, x:QLineEdit, y:1~7 */
#define SCENE_SETUP_CREATE_EDIT(x,y)        \
    SCENE_SETUP_WIDGET((x),y,SCENE_SETUP_COL_WIDTH_EDIT)

//编辑框 常用
#define SCENE_SETUP_CREATE_LINEEDIT(x,y)        \
    do {                                        \
        SCENE_SETUP_CREATE_EDIT((x),y);           \
        LINEEDIT_STYLE(x);                      \
    } while(0)

//显示样式
#define SCENE_SETUP_CREATE_SHOWSTYLE(x,y)        \
    do {                                        \
        SCENE_SETUP_CREATE_EDIT((x),y);           \
        LINEEDIT_SHOWSTYLE(x);                      \
    } while(0)

//值
/* Create a value table, x:QLabel, y:1~7 */
#define SCENE_SETUP_CREATE_VALUE(x,y)           \
    do {                                        \
        SCENE_SETUP_CREATE_EDIT(x,y);           \
        x.setFont(QFont(QString(CONFIG_FONT_STYLE),         \
            CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL));      \
        x.setAlignment(Qt::AlignCenter);        \
        x.setStyleSheet(CONFIG_COLOR_LABEL);    \
    } while(0)

//选择框
/* Create a value QComboBox, x:QComboBox, y:1~7 */
#define SCENE_SETUP_CREATE_COMBOBOX(x,y)        \
    do {                                        \
        (x).setGeometry(QRect(SCENE_SETUP_COL_LINEEDIT,   \
                    SCENE_SETUP_ROW_##y+4,              \
                    SCENE_SETUP_COL_WIDTH_COMBOBOX,     \
                    SCENE_SETUP_WIDGET_HIGH-4));        \
        (x).setFont(QFont(QString(CONFIG_FONT_STYLE),     \
                    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
        COMBOBOX_STYLE(x);                      \
    } while(0)

//单位标签
/* Create a unit table, x:QLabel, y:1~7 */
#define SCENE_SETUP_CREATE_UNIT(x,y)            \
        do {                                    \
            (x).setGeometry(QRect(SCENE_SETUP_COL_UNIT,       \
                        SCENE_SETUP_ROW_##y,                \
                        SCENE_SETUP_COL_WIDTH_UNIT,         \
                        SCENE_SETUP_WIDGET_HIGH));          \
            (x).setAlignment( Qt::AlignVCenter | Qt::AlignLeft); \
            (x).setFont(QFont(QString(CONFIG_FONT_STYLE),     \
                        CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
            (x).setStyleSheet(CONFIG_COLOR_LABEL);    \
        } while(0)
			
		
/*---------------KTV界面自己的--------------*/
#define SCENE_PATIENT_LABEL_X       0
#define SCENE_PATIENT_UNIT_X        340
#define SCENE_PATIENT_LINEEDIT_X    215
#define SCENE_DIALYSIS_LABEL_X    0
#define SCENE_DISLYSIS_UNIT_X     420
#define SCENE_DISLYSIS_LINEEDIT_X 305

#define SCENE_KTV_LABEL_Y_0 10
#define SCENE_KTV_LABEL_Y_1 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_0 + 7)//55
#define SCENE_KTV_LABEL_Y_2 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_1 + 7)//100
#define SCENE_KTV_LABEL_Y_3 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_2 + 7)//145
#define SCENE_KTV_LABEL_Y_4 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_3 + 7)//190
#define SCENE_KTV_LABEL_Y_5 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_4 + 7)//235
#define SCENE_KTV_LABEL_Y_6 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_5 + 7)//280
#define SCENE_KTV_LABEL_Y_7 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_6 + 7)//325
#define SCENE_KTV_LABEL_Y_8 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_7 + 7)//370
#define SCENE_KTV_LABEL_Y_9 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_8 + 7)//415
#define SCENE_KTV_LABEL_Y_10 (SCENE_SETUP_WIDGET_HIGH + SCENE_KTV_LABEL_Y_9 + 7)//460

#define SCENE_KTV_LABLE(p,x,y,w)           \
    do {                                        \
    (p).setGeometry(QRect(x,          \
    SCENE_KTV_LABEL_Y_##y, (w),                \
    SCENE_SETUP_WIDGET_HIGH));                \
    (p).setAlignment( Qt::AlignVCenter | Qt::AlignRight); \
    (p).setFont(QFont(QString(CONFIG_FONT_STYLE),         \
    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (p).setStyleSheet(CONFIG_COLOR_LABEL);                \
    } while(0)

#define SCENE_KTV2_DIS_LABLE(p,x,y,w)           \
    do {                                        \
    (p).setGeometry(QRect(x,          \
    y, (w),                \
    38));                \
    (p).setAlignment( Qt::AlignVCenter | Qt::AlignRight); \
    (p).setFont(QFont(QString(CONFIG_FONT_STYLE),         \
    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (p).setStyleSheet(CONFIG_COLOR_LABEL);                \
    } while(0)

#define SCENE_KTV2_LINEEDIT(p,x,y)        \
    do {                                        \
    (p).setGeometry(QRect((x), y, \
    SCENE_SETUP_COL_WIDTH_EDIT,SCENE_SETUP_WIDGET_HIGH));\
    LINEEDIT_STYLE(p);                      \
    } while(0)

#define SCENE_KTV2_UNIT(p,x,y)            \
    do {                                    \
    (p).setGeometry(QRect(x,       \
    y,                \
    SCENE_SETUP_COL_WIDTH_UNIT,         \
    SCENE_SETUP_WIDGET_HIGH));          \
    (p).setAlignment( Qt::AlignVCenter | Qt::AlignLeft); \
    (p).setFont(QFont(QString(CONFIG_FONT_STYLE),     \
    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (p).setStyleSheet(CONFIG_COLOR_LABEL);    \
    } while(0)

#define SCENE_KTV_UNIT(p,x,y)            \
    do {                                    \
    (p).setGeometry(QRect(x,       \
    SCENE_KTV_LABEL_Y_##y,                \
    SCENE_SETUP_COL_WIDTH_UNIT,         \
    SCENE_SETUP_WIDGET_HIGH));          \
    (p).setAlignment( Qt::AlignVCenter | Qt::AlignLeft); \
    (p).setFont(QFont(QString(CONFIG_FONT_STYLE),     \
    CFG_FONT_SIZE_THIRD, CONFIG_FONT_NORMAL)); \
    (p).setStyleSheet(CONFIG_COLOR_LABEL);    \
    } while(0)

#define SCENE_KTV_EDIT(p, x, y)  \
    do {                                        \
    (p).setGeometry(QRect((x), SCENE_KTV_LABEL_Y_##y, \
    SCENE_SETUP_COL_WIDTH_EDIT,SCENE_SETUP_WIDGET_HIGH));\
    } while(0)

#define SCENE_KTV_LINEEDIT(p,x,y)        \
    do {                                        \
    SCENE_KTV_EDIT((p), x, y);           \
    LINEEDIT_STYLE(p);                      \
    } while(0)
#endif