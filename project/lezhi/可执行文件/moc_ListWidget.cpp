/****************************************************************************
** Meta object code from reading C++ file 'ListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../01-22-VideoPlayer/ListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListWidget_t {
    QByteArrayData data[16];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidget_t qt_meta_stringdata_ListWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ListWidget"
QT_MOC_LITERAL(1, 11, 15), // "ItemDoubleClick"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "name"
QT_MOC_LITERAL(4, 33, 11), // "ItemDeleted"
QT_MOC_LITERAL(5, 45, 1), // "n"
QT_MOC_LITERAL(6, 47, 14), // "signalClearAll"
QT_MOC_LITERAL(7, 62, 16), // "signalActionOpen"
QT_MOC_LITERAL(8, 79, 20), // "signalClearValidItem"
QT_MOC_LITERAL(9, 100, 19), // "signalOpenDirectory"
QT_MOC_LITERAL(10, 120, 14), // "slotActionOpen"
QT_MOC_LITERAL(11, 135, 20), // "slotActionDeleteItem"
QT_MOC_LITERAL(12, 156, 24), // "slotActionClearValidItem"
QT_MOC_LITERAL(13, 181, 18), // "slotActionClearAll"
QT_MOC_LITERAL(14, 200, 14), // "slotActionPlay"
QT_MOC_LITERAL(15, 215, 23) // "slotActionOpenDirectory"

    },
    "ListWidget\0ItemDoubleClick\0\0name\0"
    "ItemDeleted\0n\0signalClearAll\0"
    "signalActionOpen\0signalClearValidItem\0"
    "signalOpenDirectory\0slotActionOpen\0"
    "slotActionDeleteItem\0slotActionClearValidItem\0"
    "slotActionClearAll\0slotActionPlay\0"
    "slotActionOpenDirectory"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    0,   80,    2, 0x06 /* Public */,
       7,    0,   81,    2, 0x06 /* Public */,
       8,    0,   82,    2, 0x06 /* Public */,
       9,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   86,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    0,   88,    2, 0x0a /* Public */,
      13,    0,   89,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidget *_t = static_cast<ListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ItemDoubleClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ItemDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalClearAll(); break;
        case 3: _t->signalActionOpen(); break;
        case 4: _t->signalClearValidItem(); break;
        case 5: _t->signalOpenDirectory((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotActionOpen(); break;
        case 7: _t->slotActionDeleteItem(); break;
        case 8: _t->slotActionClearValidItem(); break;
        case 9: _t->slotActionClearAll(); break;
        case 10: _t->slotActionPlay(); break;
        case 11: _t->slotActionOpenDirectory(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::ItemDoubleClick)) {
                *result = 0;
            }
        }
        {
            typedef void (ListWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::ItemDeleted)) {
                *result = 1;
            }
        }
        {
            typedef void (ListWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::signalClearAll)) {
                *result = 2;
            }
        }
        {
            typedef void (ListWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::signalActionOpen)) {
                *result = 3;
            }
        }
        {
            typedef void (ListWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::signalClearValidItem)) {
                *result = 4;
            }
        }
        {
            typedef void (ListWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::signalOpenDirectory)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject ListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ListWidget.data,
      qt_meta_data_ListWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidget.stringdata0))
        return static_cast<void*>(const_cast< ListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ListWidget::ItemDoubleClick(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ListWidget::ItemDeleted(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ListWidget::signalClearAll()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ListWidget::signalActionOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ListWidget::signalClearValidItem()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void ListWidget::signalOpenDirectory(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
