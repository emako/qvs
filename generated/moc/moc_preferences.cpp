/****************************************************************************
** Meta object code from reading C++ file 'preferences.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../com/preferences.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preferences.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Preferences_t {
    QByteArrayData data[16];
    char stringdata0[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Preferences_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Preferences_t qt_meta_stringdata_Preferences = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Preferences"
QT_MOC_LITERAL(1, 12, 10), // "closeEvent"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "QCloseEvent*"
QT_MOC_LITERAL(4, 37, 33), // "on_comboBoxStyleFactory_activ..."
QT_MOC_LITERAL(5, 71, 6), // "a_text"
QT_MOC_LITERAL(6, 78, 29), // "on_comboBoxPriority_activated"
QT_MOC_LITERAL(7, 108, 7), // "a_index"
QT_MOC_LITERAL(8, 116, 34), // "on_checkNotRunNextJob_stateCh..."
QT_MOC_LITERAL(9, 151, 7), // "a_state"
QT_MOC_LITERAL(10, 159, 40), // "on_checkNotShowSplashScreen_s..."
QT_MOC_LITERAL(11, 200, 32), // "on_checkUse32BitAVS_stateChanged"
QT_MOC_LITERAL(12, 233, 22), // "on_resetButton_clicked"
QT_MOC_LITERAL(13, 256, 19), // "on_buttonDG_clicked"
QT_MOC_LITERAL(14, 276, 21), // "on_buttonDGNV_clicked"
QT_MOC_LITERAL(15, 298, 22) // "on_closeButton_clicked"

    },
    "Preferences\0closeEvent\0\0QCloseEvent*\0"
    "on_comboBoxStyleFactory_activated\0"
    "a_text\0on_comboBoxPriority_activated\0"
    "a_index\0on_checkNotRunNextJob_stateChanged\0"
    "a_state\0on_checkNotShowSplashScreen_stateChanged\0"
    "on_checkUse32BitAVS_stateChanged\0"
    "on_resetButton_clicked\0on_buttonDG_clicked\0"
    "on_buttonDGNV_clicked\0on_closeButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Preferences[] = {

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
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       6,    1,   70,    2, 0x08 /* Private */,
       8,    1,   73,    2, 0x08 /* Private */,
      10,    1,   76,    2, 0x08 /* Private */,
      11,    1,   79,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Preferences::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Preferences *_t = static_cast<Preferences *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->on_comboBoxStyleFactory_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_comboBoxPriority_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_checkNotRunNextJob_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkNotShowSplashScreen_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkUse32BitAVS_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_resetButton_clicked(); break;
        case 7: _t->on_buttonDG_clicked(); break;
        case 8: _t->on_buttonDGNV_clicked(); break;
        case 9: _t->on_closeButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Preferences::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Preferences.data,
      qt_meta_data_Preferences,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Preferences::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Preferences::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Preferences.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Preferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
