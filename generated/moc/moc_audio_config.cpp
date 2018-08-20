/****************************************************************************
** Meta object code from reading C++ file 'audio_config.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tools/audio_config.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audio_config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioConfig_t {
    QByteArrayData data[9];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioConfig_t qt_meta_stringdata_AudioConfig = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioConfig"
QT_MOC_LITERAL(1, 12, 11), // "resizeEvent"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "QResizeEvent*"
QT_MOC_LITERAL(4, 39, 1), // "e"
QT_MOC_LITERAL(5, 41, 23), // "on_buttonAccept_clicked"
QT_MOC_LITERAL(6, 65, 23), // "on_buttonCancel_clicked"
QT_MOC_LITERAL(7, 89, 43), // "on_comboBoxAudioEncoder_curre..."
QT_MOC_LITERAL(8, 133, 7) // "a_index"

    },
    "AudioConfig\0resizeEvent\0\0QResizeEvent*\0"
    "e\0on_buttonAccept_clicked\0"
    "on_buttonCancel_clicked\0"
    "on_comboBoxAudioEncoder_currentIndexChanged\0"
    "a_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x08 /* Private */,
       7,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void AudioConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AudioConfig *_t = static_cast<AudioConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 1: _t->on_buttonAccept_clicked(); break;
        case 2: _t->on_buttonCancel_clicked(); break;
        case 3: _t->on_comboBoxAudioEncoder_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AudioConfig::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AudioConfig.data,
      qt_meta_data_AudioConfig,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AudioConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioConfig.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AudioConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
