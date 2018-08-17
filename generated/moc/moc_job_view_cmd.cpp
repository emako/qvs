/****************************************************************************
** Meta object code from reading C++ file 'job_view_cmd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../job/job_view_cmd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'job_view_cmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JobViewCmd_t {
    QByteArrayData data[6];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JobViewCmd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JobViewCmd_t qt_meta_stringdata_JobViewCmd = {
    {
QT_MOC_LITERAL(0, 0, 10), // "JobViewCmd"
QT_MOC_LITERAL(1, 11, 34), // "on_checkBoxShowDetail_stateCh..."
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 7), // "a_state"
QT_MOC_LITERAL(4, 55, 21), // "on_buttonSave_clicked"
QT_MOC_LITERAL(5, 77, 21) // "on_buttonCopy_clicked"

    },
    "JobViewCmd\0on_checkBoxShowDetail_stateChanged\0"
    "\0a_state\0on_buttonSave_clicked\0"
    "on_buttonCopy_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JobViewCmd[] = {

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
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void JobViewCmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JobViewCmd *_t = static_cast<JobViewCmd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_checkBoxShowDetail_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_buttonSave_clicked(); break;
        case 2: _t->on_buttonCopy_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JobViewCmd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JobViewCmd.data,
      qt_meta_data_JobViewCmd,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JobViewCmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JobViewCmd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JobViewCmd.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int JobViewCmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
