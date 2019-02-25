/****************************************************************************
** Meta object code from reading C++ file 'musiclist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../musiclist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musiclist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MusicList_t {
    QByteArrayData data[14];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicList_t qt_meta_stringdata_MusicList = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MusicList"
QT_MOC_LITERAL(1, 10, 13), // "playlistClean"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "addMedia"
QT_MOC_LITERAL(4, 34, 18), // "List_0_IndexChange"
QT_MOC_LITERAL(5, 53, 18), // "list_1_IndexChange"
QT_MOC_LITERAL(6, 72, 11), // "remove_sign"
QT_MOC_LITERAL(7, 84, 9), // "show_hide"
QT_MOC_LITERAL(8, 94, 20), // "list_0_current_index"
QT_MOC_LITERAL(9, 115, 5), // "index"
QT_MOC_LITERAL(10, 121, 20), // "list_1_current_index"
QT_MOC_LITERAL(11, 142, 12), // "remove_inedx"
QT_MOC_LITERAL(12, 155, 12), // "addMediaPlay"
QT_MOC_LITERAL(13, 168, 13) // "clearPlaylist"

    },
    "MusicList\0playlistClean\0\0addMedia\0"
    "List_0_IndexChange\0list_1_IndexChange\0"
    "remove_sign\0show_hide\0list_0_current_index\0"
    "index\0list_1_current_index\0remove_inedx\0"
    "addMediaPlay\0clearPlaylist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       5,    1,   74,    2, 0x06 /* Public */,
       6,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   78,    2, 0x0a /* Public */,
       8,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      11,    0,   85,    2, 0x0a /* Public */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    9,
    QMetaType::Void, QMetaType::QModelIndex,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MusicList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MusicList *_t = static_cast<MusicList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playlistClean(); break;
        case 1: _t->addMedia(); break;
        case 2: _t->List_0_IndexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->list_1_IndexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->remove_sign(); break;
        case 5: _t->show_hide(); break;
        case 6: _t->list_0_current_index((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: _t->list_1_current_index((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: _t->remove_inedx(); break;
        case 9: _t->addMediaPlay(); break;
        case 10: _t->clearPlaylist(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MusicList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicList::playlistClean)) {
                *result = 0;
            }
        }
        {
            typedef void (MusicList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicList::addMedia)) {
                *result = 1;
            }
        }
        {
            typedef void (MusicList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicList::List_0_IndexChange)) {
                *result = 2;
            }
        }
        {
            typedef void (MusicList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicList::list_1_IndexChange)) {
                *result = 3;
            }
        }
        {
            typedef void (MusicList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicList::remove_sign)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject MusicList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicList.data,
      qt_meta_data_MusicList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MusicList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MusicList.stringdata0))
        return static_cast<void*>(const_cast< MusicList*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MusicList::playlistClean()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MusicList::addMedia()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MusicList::List_0_IndexChange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicList::list_1_IndexChange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MusicList::remove_sign()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
