/****************************************************************************
** Meta object code from reading C++ file 'installer_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tools/installer_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'installer_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InstallerDialog_t {
    QByteArrayData data[18];
    char stringdata0[407];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InstallerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InstallerDialog_t qt_meta_stringdata_InstallerDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "InstallerDialog"
QT_MOC_LITERAL(1, 16, 27), // "slotInstallerProcessStarted"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 43), // "slotInstallerProcessReadyRead..."
QT_MOC_LITERAL(4, 89, 42), // "slotInstallerProcessReadyRead..."
QT_MOC_LITERAL(5, 132, 28), // "slotInstallerProcessFinished"
QT_MOC_LITERAL(6, 161, 10), // "a_exitCode"
QT_MOC_LITERAL(7, 172, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 193, 12), // "a_exitStatus"
QT_MOC_LITERAL(9, 206, 25), // "slotInstallerProcessError"
QT_MOC_LITERAL(10, 232, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(11, 255, 7), // "a_error"
QT_MOC_LITERAL(12, 263, 33), // "on_checkBoxUninstall_stateCha..."
QT_MOC_LITERAL(13, 297, 4), // "arg1"
QT_MOC_LITERAL(14, 302, 26), // "on_buttonSecletAll_clicked"
QT_MOC_LITERAL(15, 329, 27), // "on_buttonSelectNone_clicked"
QT_MOC_LITERAL(16, 357, 24), // "on_buttonDefault_clicked"
QT_MOC_LITERAL(17, 382, 24) // "on_buttonInstall_clicked"

    },
    "InstallerDialog\0slotInstallerProcessStarted\0"
    "\0slotInstallerProcessReadyReadStandardOutput\0"
    "slotInstallerProcessReadyReadStandardError\0"
    "slotInstallerProcessFinished\0a_exitCode\0"
    "QProcess::ExitStatus\0a_exitStatus\0"
    "slotInstallerProcessError\0"
    "QProcess::ProcessError\0a_error\0"
    "on_checkBoxUninstall_stateChanged\0"
    "arg1\0on_buttonSecletAll_clicked\0"
    "on_buttonSelectNone_clicked\0"
    "on_buttonDefault_clicked\0"
    "on_buttonInstall_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InstallerDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    2,   67,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      12,    1,   75,    2, 0x08 /* Private */,
      14,    0,   78,    2, 0x08 /* Private */,
      15,    0,   79,    2, 0x08 /* Private */,
      16,    0,   80,    2, 0x08 /* Private */,
      17,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InstallerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InstallerDialog *_t = static_cast<InstallerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotInstallerProcessStarted(); break;
        case 1: _t->slotInstallerProcessReadyReadStandardOutput(); break;
        case 2: _t->slotInstallerProcessReadyReadStandardError(); break;
        case 3: _t->slotInstallerProcessFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->slotInstallerProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 5: _t->on_checkBoxUninstall_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_buttonSecletAll_clicked(); break;
        case 7: _t->on_buttonSelectNone_clicked(); break;
        case 8: _t->on_buttonDefault_clicked(); break;
        case 9: _t->on_buttonInstall_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InstallerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InstallerDialog.data,
      qt_meta_data_InstallerDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InstallerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InstallerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InstallerDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InstallerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
