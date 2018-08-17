/****************************************************************************
** Meta object code from reading C++ file 'demuxer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tools/demuxer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'demuxer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Demuxer_t {
    QByteArrayData data[22];
    char stringdata0[514];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Demuxer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Demuxer_t qt_meta_stringdata_Demuxer = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Demuxer"
QT_MOC_LITERAL(1, 8, 25), // "slotEncoderProcessStarted"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 40), // "slotEncoderProcessReadyReadSt..."
QT_MOC_LITERAL(4, 76, 41), // "slotEncoderProcessReadyReadSt..."
QT_MOC_LITERAL(5, 118, 26), // "slotEncoderProcessFinished"
QT_MOC_LITERAL(6, 145, 10), // "a_exitCode"
QT_MOC_LITERAL(7, 156, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 177, 12), // "a_exitStatus"
QT_MOC_LITERAL(9, 190, 23), // "slotEncoderProcessError"
QT_MOC_LITERAL(10, 214, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(11, 237, 7), // "a_error"
QT_MOC_LITERAL(12, 245, 16), // "slotStartLoading"
QT_MOC_LITERAL(13, 262, 15), // "slotStopLoading"
QT_MOC_LITERAL(14, 278, 44), // "on_comboBoxDemuxerFormat_curr..."
QT_MOC_LITERAL(15, 323, 7), // "a_index"
QT_MOC_LITERAL(16, 331, 29), // "on_buttonDemuxerStart_clicked"
QT_MOC_LITERAL(17, 361, 36), // "on_listWidgetTrack_currentRow..."
QT_MOC_LITERAL(18, 398, 5), // "a_row"
QT_MOC_LITERAL(19, 404, 43), // "on_comboBoxDemuxerParam_curre..."
QT_MOC_LITERAL(20, 448, 34), // "on_buttonDemuxerVideoInput_cl..."
QT_MOC_LITERAL(21, 483, 30) // "on_buttonDemuxerOutput_clicked"

    },
    "Demuxer\0slotEncoderProcessStarted\0\0"
    "slotEncoderProcessReadyReadStandardError\0"
    "slotEncoderProcessReadyReadStandardOutput\0"
    "slotEncoderProcessFinished\0a_exitCode\0"
    "QProcess::ExitStatus\0a_exitStatus\0"
    "slotEncoderProcessError\0QProcess::ProcessError\0"
    "a_error\0slotStartLoading\0slotStopLoading\0"
    "on_comboBoxDemuxerFormat_currentIndexChanged\0"
    "a_index\0on_buttonDemuxerStart_clicked\0"
    "on_listWidgetTrack_currentRowChanged\0"
    "a_row\0on_comboBoxDemuxerParam_currentIndexChanged\0"
    "on_buttonDemuxerVideoInput_clicked\0"
    "on_buttonDemuxerOutput_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Demuxer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    2,   82,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    1,   92,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,
      17,    1,   96,    2, 0x08 /* Private */,
      19,    1,   99,    2, 0x08 /* Private */,
      20,    0,  102,    2, 0x08 /* Private */,
      21,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Demuxer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Demuxer *_t = static_cast<Demuxer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotEncoderProcessStarted(); break;
        case 1: _t->slotEncoderProcessReadyReadStandardError(); break;
        case 2: _t->slotEncoderProcessReadyReadStandardOutput(); break;
        case 3: _t->slotEncoderProcessFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->slotEncoderProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 5: _t->slotStartLoading(); break;
        case 6: _t->slotStopLoading(); break;
        case 7: _t->on_comboBoxDemuxerFormat_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_buttonDemuxerStart_clicked(); break;
        case 9: _t->on_listWidgetTrack_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_comboBoxDemuxerParam_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_buttonDemuxerVideoInput_clicked(); break;
        case 12: _t->on_buttonDemuxerOutput_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Demuxer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Demuxer.data,
      qt_meta_data_Demuxer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Demuxer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Demuxer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Demuxer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Demuxer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
