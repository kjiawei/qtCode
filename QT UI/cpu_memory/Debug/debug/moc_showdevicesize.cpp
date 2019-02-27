/****************************************************************************
** Meta object code from reading C++ file 'showdevicesize.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../showdevicesize.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showdevicesize.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowDeviceSize_t {
    QByteArrayData data[11];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowDeviceSize_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowDeviceSize_t qt_meta_stringdata_ShowDeviceSize = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ShowDeviceSize"
QT_MOC_LITERAL(1, 15, 8), // "ReadData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "CheckSize"
QT_MOC_LITERAL(4, 35, 6), // "result"
QT_MOC_LITERAL(5, 42, 4), // "name"
QT_MOC_LITERAL(6, 47, 10), // "InsertSize"
QT_MOC_LITERAL(7, 58, 3), // "use"
QT_MOC_LITERAL(8, 62, 4), // "free"
QT_MOC_LITERAL(9, 67, 3), // "all"
QT_MOC_LITERAL(10, 71, 7) // "percent"

    },
    "ShowDeviceSize\0ReadData\0\0CheckSize\0"
    "result\0name\0InsertSize\0use\0free\0all\0"
    "percent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowDeviceSize[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    2,   30,    2, 0x08 /* Private */,
       6,    5,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    5,    7,    8,    9,   10,

       0        // eod
};

void ShowDeviceSize::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowDeviceSize *_t = static_cast<ShowDeviceSize *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReadData(); break;
        case 1: _t->CheckSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->InsertSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObject ShowDeviceSize::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShowDeviceSize.data,
      qt_meta_data_ShowDeviceSize,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowDeviceSize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowDeviceSize::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowDeviceSize.stringdata0))
        return static_cast<void*>(const_cast< ShowDeviceSize*>(this));
    return QObject::qt_metacast(_clname);
}

int ShowDeviceSize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
