/****************************************************************************
** Meta object code from reading C++ file 'job_creator_help.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../job/job_creator_help.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'job_creator_help.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JobCreatorHelp_t {
    QByteArrayData data[12];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JobCreatorHelp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JobCreatorHelp_t qt_meta_stringdata_JobCreatorHelp = {
    {
QT_MOC_LITERAL(0, 0, 14), // "JobCreatorHelp"
QT_MOC_LITERAL(1, 15, 18), // "slotProcessStarted"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 33), // "slotProcessReadyReadStandardE..."
QT_MOC_LITERAL(4, 69, 34), // "slotProcessReadyReadStandardO..."
QT_MOC_LITERAL(5, 104, 19), // "slotProcessFinished"
QT_MOC_LITERAL(6, 124, 10), // "a_exitCode"
QT_MOC_LITERAL(7, 135, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 156, 12), // "a_exitStatus"
QT_MOC_LITERAL(9, 169, 16), // "slotProcessError"
QT_MOC_LITERAL(10, 186, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(11, 209, 7) // "a_error"

    },
    "JobCreatorHelp\0slotProcessStarted\0\0"
    "slotProcessReadyReadStandardError\0"
    "slotProcessReadyReadStandardOutput\0"
    "slotProcessFinished\0a_exitCode\0"
    "QProcess::ExitStatus\0a_exitStatus\0"
    "slotProcessError\0QProcess::ProcessError\0"
    "a_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JobCreatorHelp[] = {

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
       1,    0,   39,    2, 0x09 /* Protected */,
       3,    0,   40,    2, 0x09 /* Protected */,
       4,    0,   41,    2, 0x09 /* Protected */,
       5,    2,   42,    2, 0x09 /* Protected */,
       9,    1,   47,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void JobCreatorHelp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JobCreatorHelp *_t = static_cast<JobCreatorHelp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotProcessStarted(); break;
        case 1: _t->slotProcessReadyReadStandardError(); break;
        case 2: _t->slotProcessReadyReadStandardOutput(); break;
        case 3: _t->slotProcessFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->slotProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JobCreatorHelp::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JobCreatorHelp.data,
      qt_meta_data_JobCreatorHelp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JobCreatorHelp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JobCreatorHelp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JobCreatorHelp.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int JobCreatorHelp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
