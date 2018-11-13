/****************************************************************************
** Meta object code from reading C++ file 'ps_m_wnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ps_m_wnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ps_m_wnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PS_M_Wnd_t {
    QByteArrayData data[13];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PS_M_Wnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PS_M_Wnd_t qt_meta_stringdata_PS_M_Wnd = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PS_M_Wnd"
QT_MOC_LITERAL(1, 9, 18), // "on_btn_cmd_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "on_btn_scr_clicked"
QT_MOC_LITERAL(4, 48, 11), // "slot_online"
QT_MOC_LITERAL(5, 60, 10), // "Line_Data*"
QT_MOC_LITERAL(6, 71, 6), // "p_data"
QT_MOC_LITERAL(7, 78, 15), // "slot_create_dlg"
QT_MOC_LITERAL(8, 94, 15), // "Client_Session*"
QT_MOC_LITERAL(9, 110, 4), // "p_cs"
QT_MOC_LITERAL(10, 115, 6), // "n_type"
QT_MOC_LITERAL(11, 122, 14), // "slot_recv_data"
QT_MOC_LITERAL(12, 137, 3) // "buf"

    },
    "PS_M_Wnd\0on_btn_cmd_clicked\0\0"
    "on_btn_scr_clicked\0slot_online\0"
    "Line_Data*\0p_data\0slot_create_dlg\0"
    "Client_Session*\0p_cs\0n_type\0slot_recv_data\0"
    "buf"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PS_M_Wnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    1,   41,    2, 0x0a /* Public */,
       7,    2,   44,    2, 0x0a /* Public */,
      11,    3,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::QByteArray,    9,   10,   12,

       0        // eod
};

void PS_M_Wnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PS_M_Wnd *_t = static_cast<PS_M_Wnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_cmd_clicked(); break;
        case 1: _t->on_btn_scr_clicked(); break;
        case 2: _t->slot_online((*reinterpret_cast< Line_Data*(*)>(_a[1]))); break;
        case 3: _t->slot_create_dlg((*reinterpret_cast< Client_Session*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_recv_data((*reinterpret_cast< Client_Session*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject PS_M_Wnd::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PS_M_Wnd.data,
      qt_meta_data_PS_M_Wnd,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PS_M_Wnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PS_M_Wnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PS_M_Wnd.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PS_M_Wnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
