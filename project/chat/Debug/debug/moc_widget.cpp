/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[20];
    char stringdata0[348];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 24), // "on_textUnderline_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "checked"
QT_MOC_LITERAL(4, 41, 16), // "on_clear_clicked"
QT_MOC_LITERAL(5, 58, 15), // "on_save_clicked"
QT_MOC_LITERAL(6, 74, 20), // "on_textcolor_clicked"
QT_MOC_LITERAL(7, 95, 21), // "on_textitalic_clicked"
QT_MOC_LITERAL(8, 117, 19), // "on_textbold_clicked"
QT_MOC_LITERAL(9, 137, 34), // "on_fontComboBox_currentFontCh..."
QT_MOC_LITERAL(10, 172, 1), // "f"
QT_MOC_LITERAL(11, 174, 39), // "on_fontsizecomboBox_currentIn..."
QT_MOC_LITERAL(12, 214, 16), // "on_close_clicked"
QT_MOC_LITERAL(13, 231, 19), // "on_sendfile_clicked"
QT_MOC_LITERAL(14, 251, 15), // "on_send_clicked"
QT_MOC_LITERAL(15, 267, 23), // "processPendingDatagrams"
QT_MOC_LITERAL(16, 291, 12), // "sentFileName"
QT_MOC_LITERAL(17, 304, 20), // "currentFormatChanged"
QT_MOC_LITERAL(18, 325, 15), // "QTextCharFormat"
QT_MOC_LITERAL(19, 341, 6) // "format"

    },
    "Widget\0on_textUnderline_clicked\0\0"
    "checked\0on_clear_clicked\0on_save_clicked\0"
    "on_textcolor_clicked\0on_textitalic_clicked\0"
    "on_textbold_clicked\0"
    "on_fontComboBox_currentFontChanged\0f\0"
    "on_fontsizecomboBox_currentIndexChanged\0"
    "on_close_clicked\0on_sendfile_clicked\0"
    "on_send_clicked\0processPendingDatagrams\0"
    "sentFileName\0currentFormatChanged\0"
    "QTextCharFormat\0format"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    1,   90,    2, 0x08 /* Private */,
       8,    1,   93,    2, 0x08 /* Private */,
       9,    1,   96,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      17,    1,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QFont,   10,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_textUnderline_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_clear_clicked(); break;
        case 2: _t->on_save_clicked(); break;
        case 3: _t->on_textcolor_clicked(); break;
        case 4: _t->on_textitalic_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_textbold_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_fontComboBox_currentFontChanged((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 7: _t->on_fontsizecomboBox_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_close_clicked(); break;
        case 9: _t->on_sendfile_clicked(); break;
        case 10: _t->on_send_clicked(); break;
        case 11: _t->processPendingDatagrams(); break;
        case 12: _t->sentFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->currentFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
