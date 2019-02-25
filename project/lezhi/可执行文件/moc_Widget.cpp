/****************************************************************************
** Meta object code from reading C++ file 'Widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../01-22-VideoPlayer/Widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[46];
    char stringdata0[821];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 14), // "signalInRegion"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "signalOutRegion"
QT_MOC_LITERAL(4, 39, 13), // "slotSetButton"
QT_MOC_LITERAL(5, 53, 12), // "slotOpenFile"
QT_MOC_LITERAL(6, 66, 12), // "slotSetValue"
QT_MOC_LITERAL(7, 79, 5), // "value"
QT_MOC_LITERAL(8, 85, 16), // "slotStateChanged"
QT_MOC_LITERAL(9, 102, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(10, 122, 19), // "slotDurationChanged"
QT_MOC_LITERAL(11, 142, 19), // "slotPositionChanged"
QT_MOC_LITERAL(12, 162, 15), // "slotPlayOrPause"
QT_MOC_LITERAL(13, 178, 13), // "slotNextVideo"
QT_MOC_LITERAL(14, 192, 13), // "slotLastVideo"
QT_MOC_LITERAL(15, 206, 13), // "slotStopVideo"
QT_MOC_LITERAL(16, 220, 15), // "slotVolumeTimer"
QT_MOC_LITERAL(17, 236, 17), // "slotPlayModeTimer"
QT_MOC_LITERAL(18, 254, 22), // "slotPlayModeListWidget"
QT_MOC_LITERAL(19, 277, 18), // "slotInBottomRegion"
QT_MOC_LITERAL(20, 296, 19), // "slotOutBottomRegion"
QT_MOC_LITERAL(21, 316, 24), // "slotOutBottomRegionTimer"
QT_MOC_LITERAL(22, 341, 23), // "slotSignalPressPosition"
QT_MOC_LITERAL(23, 365, 8), // "position"
QT_MOC_LITERAL(24, 374, 23), // "slotPressVolumePosition"
QT_MOC_LITERAL(25, 398, 29), // "slotListWidgetItemDoubleClick"
QT_MOC_LITERAL(26, 428, 4), // "name"
QT_MOC_LITERAL(27, 433, 25), // "slotListWidgetItemDeleted"
QT_MOC_LITERAL(28, 459, 1), // "n"
QT_MOC_LITERAL(29, 461, 19), // "slotSignalMovePoint"
QT_MOC_LITERAL(30, 481, 28), // "slotVideoWidgetMouseLeftDown"
QT_MOC_LITERAL(31, 510, 15), // "slotHandleError"
QT_MOC_LITERAL(32, 526, 28), // "slotVideoWidgetDoubleClicked"
QT_MOC_LITERAL(33, 555, 22), // "slotListWidgetClearAll"
QT_MOC_LITERAL(34, 578, 24), // "slotListWidgetActionOpen"
QT_MOC_LITERAL(35, 603, 14), // "slotHideButton"
QT_MOC_LITERAL(36, 618, 17), // "slotInRightRegion"
QT_MOC_LITERAL(37, 636, 18), // "slotOutRightRegion"
QT_MOC_LITERAL(38, 655, 23), // "slotOutRightRegionTimer"
QT_MOC_LITERAL(39, 679, 15), // "slotCloseWidget"
QT_MOC_LITERAL(40, 695, 25), // "slotVideoWidgetDropedList"
QT_MOC_LITERAL(41, 721, 11), // "QList<QUrl>"
QT_MOC_LITERAL(42, 733, 4), // "urls"
QT_MOC_LITERAL(43, 738, 28), // "slotListWidgetClearValidItem"
QT_MOC_LITERAL(44, 767, 27), // "slotListWidgetOpenDirectory"
QT_MOC_LITERAL(45, 795, 25) // "slotVideoWidgetActionInfo"

    },
    "Widget\0signalInRegion\0\0signalOutRegion\0"
    "slotSetButton\0slotOpenFile\0slotSetValue\0"
    "value\0slotStateChanged\0QMediaPlayer::State\0"
    "slotDurationChanged\0slotPositionChanged\0"
    "slotPlayOrPause\0slotNextVideo\0"
    "slotLastVideo\0slotStopVideo\0slotVolumeTimer\0"
    "slotPlayModeTimer\0slotPlayModeListWidget\0"
    "slotInBottomRegion\0slotOutBottomRegion\0"
    "slotOutBottomRegionTimer\0"
    "slotSignalPressPosition\0position\0"
    "slotPressVolumePosition\0"
    "slotListWidgetItemDoubleClick\0name\0"
    "slotListWidgetItemDeleted\0n\0"
    "slotSignalMovePoint\0slotVideoWidgetMouseLeftDown\0"
    "slotHandleError\0slotVideoWidgetDoubleClicked\0"
    "slotListWidgetClearAll\0slotListWidgetActionOpen\0"
    "slotHideButton\0slotInRightRegion\0"
    "slotOutRightRegion\0slotOutRightRegionTimer\0"
    "slotCloseWidget\0slotVideoWidgetDropedList\0"
    "QList<QUrl>\0urls\0slotListWidgetClearValidItem\0"
    "slotListWidgetOpenDirectory\0"
    "slotVideoWidgetActionInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  199,    2, 0x06 /* Public */,
       3,    0,  200,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  201,    2, 0x0a /* Public */,
       5,    0,  202,    2, 0x0a /* Public */,
       6,    1,  203,    2, 0x0a /* Public */,
       8,    1,  206,    2, 0x0a /* Public */,
      10,    1,  209,    2, 0x0a /* Public */,
      11,    1,  212,    2, 0x0a /* Public */,
      12,    0,  215,    2, 0x0a /* Public */,
      13,    0,  216,    2, 0x0a /* Public */,
      14,    0,  217,    2, 0x0a /* Public */,
      15,    0,  218,    2, 0x0a /* Public */,
      16,    0,  219,    2, 0x0a /* Public */,
      17,    0,  220,    2, 0x0a /* Public */,
      18,    0,  221,    2, 0x0a /* Public */,
      19,    0,  222,    2, 0x0a /* Public */,
      20,    0,  223,    2, 0x0a /* Public */,
      21,    0,  224,    2, 0x0a /* Public */,
      22,    1,  225,    2, 0x0a /* Public */,
      24,    1,  228,    2, 0x0a /* Public */,
      25,    1,  231,    2, 0x0a /* Public */,
      27,    1,  234,    2, 0x0a /* Public */,
      29,    1,  237,    2, 0x0a /* Public */,
      30,    1,  240,    2, 0x0a /* Public */,
      31,    0,  243,    2, 0x0a /* Public */,
      32,    0,  244,    2, 0x0a /* Public */,
      33,    0,  245,    2, 0x0a /* Public */,
      34,    0,  246,    2, 0x0a /* Public */,
      35,    0,  247,    2, 0x0a /* Public */,
      36,    0,  248,    2, 0x0a /* Public */,
      37,    0,  249,    2, 0x0a /* Public */,
      38,    0,  250,    2, 0x0a /* Public */,
      39,    0,  251,    2, 0x0a /* Public */,
      40,    1,  252,    2, 0x0a /* Public */,
      43,    0,  255,    2, 0x0a /* Public */,
      44,    1,  256,    2, 0x0a /* Public */,
      45,    0,  259,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   23,
    QMetaType::Void, QMetaType::LongLong,   23,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalInRegion(); break;
        case 1: _t->signalOutRegion(); break;
        case 2: _t->slotSetButton(); break;
        case 3: _t->slotOpenFile(); break;
        case 4: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 6: _t->slotDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->slotPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->slotPlayOrPause(); break;
        case 9: _t->slotNextVideo(); break;
        case 10: _t->slotLastVideo(); break;
        case 11: _t->slotStopVideo(); break;
        case 12: _t->slotVolumeTimer(); break;
        case 13: _t->slotPlayModeTimer(); break;
        case 14: _t->slotPlayModeListWidget(); break;
        case 15: _t->slotInBottomRegion(); break;
        case 16: _t->slotOutBottomRegion(); break;
        case 17: _t->slotOutBottomRegionTimer(); break;
        case 18: _t->slotSignalPressPosition((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 19: _t->slotPressVolumePosition((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 20: _t->slotListWidgetItemDoubleClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->slotListWidgetItemDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slotSignalMovePoint((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 23: _t->slotVideoWidgetMouseLeftDown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->slotHandleError(); break;
        case 25: _t->slotVideoWidgetDoubleClicked(); break;
        case 26: _t->slotListWidgetClearAll(); break;
        case 27: _t->slotListWidgetActionOpen(); break;
        case 28: _t->slotHideButton(); break;
        case 29: _t->slotInRightRegion(); break;
        case 30: _t->slotOutRightRegion(); break;
        case 31: _t->slotOutRightRegionTimer(); break;
        case 32: _t->slotCloseWidget(); break;
        case 33: _t->slotVideoWidgetDropedList((*reinterpret_cast< QList<QUrl>(*)>(_a[1]))); break;
        case 34: _t->slotListWidgetClearValidItem(); break;
        case 35: _t->slotListWidgetOpenDirectory((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->slotVideoWidgetActionInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QUrl> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Widget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::signalInRegion)) {
                *result = 0;
            }
        }
        {
            typedef void (Widget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::signalOutRegion)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void Widget::signalInRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Widget::signalOutRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
