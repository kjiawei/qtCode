/****************************************************************************
** Meta object code from reading C++ file 'showcpumemory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../showcpumemory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showcpumemory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowCPUMemory_t {
    QByteArrayData data[5];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowCPUMemory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowCPUMemory_t qt_meta_stringdata_ShowCPUMemory = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ShowCPUMemory"
QT_MOC_LITERAL(1, 14, 6), // "GetCPU"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "GetMemory"
QT_MOC_LITERAL(4, 32, 8) // "ReadData"

    },
    "ShowCPUMemory\0GetCPU\0\0GetMemory\0"
    "ReadData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowCPUMemory[] = {

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
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShowCPUMemory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowCPUMemory *_t = static_cast<ShowCPUMemory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetCPU(); break;
        case 1: _t->GetMemory(); break;
        case 2: _t->ReadData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ShowCPUMemory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShowCPUMemory.data,
      qt_meta_data_ShowCPUMemory,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowCPUMemory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowCPUMemory::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowCPUMemory.stringdata0))
        return static_cast<void*>(const_cast< ShowCPUMemory*>(this));
    return QObject::qt_metacast(_clname);
}

int ShowCPUMemory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
