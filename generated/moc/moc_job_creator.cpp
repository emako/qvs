/****************************************************************************
** Meta object code from reading C++ file 'job_creator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../job/job_creator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'job_creator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JobCreator_t {
    QByteArrayData data[16];
    char stringdata0[391];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JobCreator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JobCreator_t qt_meta_stringdata_JobCreator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "JobCreator"
QT_MOC_LITERAL(1, 11, 29), // "on_buttonBrowseSource_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 23), // "on_buttonAccept_clicked"
QT_MOC_LITERAL(4, 66, 23), // "on_buttonCancel_clicked"
QT_MOC_LITERAL(5, 90, 37), // "on_cbxEncoderType_currentInde..."
QT_MOC_LITERAL(6, 128, 7), // "a_index"
QT_MOC_LITERAL(7, 136, 40), // "on_cbxEncoderVariant_currentI..."
QT_MOC_LITERAL(8, 177, 41), // "on_cbxRateControlMode_current..."
QT_MOC_LITERAL(9, 219, 29), // "on_buttonBrowseOutput_clicked"
QT_MOC_LITERAL(10, 249, 29), // "on_buttonSaveTemplate_clicked"
QT_MOC_LITERAL(11, 279, 31), // "on_buttonDeleteTemplate_clicked"
QT_MOC_LITERAL(12, 311, 24), // "on_cbxTemplate_activated"
QT_MOC_LITERAL(13, 336, 5), // "a_key"
QT_MOC_LITERAL(14, 342, 43), // "on_checkBoxStartJobImmediatel..."
QT_MOC_LITERAL(15, 386, 4) // "arg1"

    },
    "JobCreator\0on_buttonBrowseSource_clicked\0"
    "\0on_buttonAccept_clicked\0"
    "on_buttonCancel_clicked\0"
    "on_cbxEncoderType_currentIndexChanged\0"
    "a_index\0on_cbxEncoderVariant_currentIndexChanged\0"
    "on_cbxRateControlMode_currentIndexChanged\0"
    "on_buttonBrowseOutput_clicked\0"
    "on_buttonSaveTemplate_clicked\0"
    "on_buttonDeleteTemplate_clicked\0"
    "on_cbxTemplate_activated\0a_key\0"
    "on_checkBoxStartJobImmediately_stateChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JobCreator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    1,   72,    2, 0x08 /* Private */,
       7,    1,   75,    2, 0x08 /* Private */,
       8,    1,   78,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    1,   84,    2, 0x08 /* Private */,
      14,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void JobCreator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JobCreator *_t = static_cast<JobCreator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buttonBrowseSource_clicked(); break;
        case 1: _t->on_buttonAccept_clicked(); break;
        case 2: _t->on_buttonCancel_clicked(); break;
        case 3: _t->on_cbxEncoderType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_cbxEncoderVariant_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_cbxRateControlMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_buttonBrowseOutput_clicked(); break;
        case 7: _t->on_buttonSaveTemplate_clicked(); break;
        case 8: _t->on_buttonDeleteTemplate_clicked(); break;
        case 9: _t->on_cbxTemplate_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_checkBoxStartJobImmediately_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JobCreator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JobCreator.data,
      qt_meta_data_JobCreator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JobCreator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JobCreator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JobCreator.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int JobCreator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
