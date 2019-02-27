/****************************************************************************
** Meta object code from reading C++ file 'BottomWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BottomWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BottomWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BottomWidget_t {
    QByteArrayData data[5];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BottomWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BottomWidget_t qt_meta_stringdata_BottomWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BottomWidget"
QT_MOC_LITERAL(1, 13, 15), // "signalMovePoint"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "signalLeftPressDown"
QT_MOC_LITERAL(4, 50, 13) // "doubleClicked"

    },
    "BottomWidget\0signalMovePoint\0\0"
    "signalLeftPressDown\0doubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BottomWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,
       4,    0,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void BottomWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BottomWidget *_t = static_cast<BottomWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMovePoint((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->signalLeftPressDown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->doubleClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BottomWidget::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BottomWidget::signalMovePoint)) {
                *result = 0;
            }
        }
        {
            typedef void (BottomWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BottomWidget::signalLeftPressDown)) {
                *result = 1;
            }
        }
        {
            typedef void (BottomWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BottomWidget::doubleClicked)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject BottomWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BottomWidget.data,
      qt_meta_data_BottomWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BottomWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BottomWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BottomWidget.stringdata0))
        return static_cast<void*>(const_cast< BottomWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BottomWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BottomWidget::signalMovePoint(QPoint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BottomWidget::signalLeftPressDown(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BottomWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
