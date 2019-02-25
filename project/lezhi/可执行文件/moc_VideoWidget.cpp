/****************************************************************************
** Meta object code from reading C++ file 'VideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../01-22-VideoPlayer/VideoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoWidget_t {
    QByteArrayData data[14];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoWidget_t qt_meta_stringdata_VideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoWidget"
QT_MOC_LITERAL(1, 12, 20), // "signalInBottomRegion"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "signalOutBottomRegion"
QT_MOC_LITERAL(4, 56, 19), // "signalInRightRegion"
QT_MOC_LITERAL(5, 76, 20), // "signalOutRightRegion"
QT_MOC_LITERAL(6, 97, 15), // "signalMovePoint"
QT_MOC_LITERAL(7, 113, 19), // "signalLeftPressDown"
QT_MOC_LITERAL(8, 133, 13), // "doubleClicked"
QT_MOC_LITERAL(9, 147, 16), // "signalDropedList"
QT_MOC_LITERAL(10, 164, 11), // "QList<QUrl>"
QT_MOC_LITERAL(11, 176, 4), // "urls"
QT_MOC_LITERAL(12, 181, 16), // "signalActionOpen"
QT_MOC_LITERAL(13, 198, 16) // "signalActionInfo"

    },
    "VideoWidget\0signalInBottomRegion\0\0"
    "signalOutBottomRegion\0signalInRightRegion\0"
    "signalOutRightRegion\0signalMovePoint\0"
    "signalLeftPressDown\0doubleClicked\0"
    "signalDropedList\0QList<QUrl>\0urls\0"
    "signalActionOpen\0signalActionInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    1,   68,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,
       8,    0,   74,    2, 0x06 /* Public */,
       9,    1,   75,    2, 0x06 /* Public */,
      12,    0,   78,    2, 0x06 /* Public */,
      13,    0,   79,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoWidget *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalInBottomRegion(); break;
        case 1: _t->signalOutBottomRegion(); break;
        case 2: _t->signalInRightRegion(); break;
        case 3: _t->signalOutRightRegion(); break;
        case 4: _t->signalMovePoint((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->signalLeftPressDown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->doubleClicked(); break;
        case 7: _t->signalDropedList((*reinterpret_cast< QList<QUrl>(*)>(_a[1]))); break;
        case 8: _t->signalActionOpen(); break;
        case 9: _t->signalActionInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
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
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalInBottomRegion)) {
                *result = 0;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalOutBottomRegion)) {
                *result = 1;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalInRightRegion)) {
                *result = 2;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalOutRightRegion)) {
                *result = 3;
            }
        }
        {
            typedef void (VideoWidget::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalMovePoint)) {
                *result = 4;
            }
        }
        {
            typedef void (VideoWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalLeftPressDown)) {
                *result = 5;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::doubleClicked)) {
                *result = 6;
            }
        }
        {
            typedef void (VideoWidget::*_t)(QList<QUrl> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalDropedList)) {
                *result = 7;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalActionOpen)) {
                *result = 8;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::signalActionInfo)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject VideoWidget::staticMetaObject = {
    { &QVideoWidget::staticMetaObject, qt_meta_stringdata_VideoWidget.data,
      qt_meta_data_VideoWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWidget.stringdata0))
        return static_cast<void*>(const_cast< VideoWidget*>(this));
    return QVideoWidget::qt_metacast(_clname);
}

int VideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVideoWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VideoWidget::signalInBottomRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VideoWidget::signalOutBottomRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void VideoWidget::signalInRightRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void VideoWidget::signalOutRightRegion()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void VideoWidget::signalMovePoint(QPoint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VideoWidget::signalLeftPressDown(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VideoWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void VideoWidget::signalDropedList(QList<QUrl> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VideoWidget::signalActionOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void VideoWidget::signalActionInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
