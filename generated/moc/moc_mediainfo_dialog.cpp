/****************************************************************************
** Meta object code from reading C++ file 'mediainfo_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tools/mediainfo_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mediainfo_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MediaInfoDialog_t {
    QByteArrayData data[28];
    char stringdata0[474];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MediaInfoDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MediaInfoDialog_t qt_meta_stringdata_MediaInfoDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MediaInfoDialog"
QT_MOC_LITERAL(1, 16, 6), // "reload"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "a_filename"
QT_MOC_LITERAL(4, 35, 11), // "slotPreview"
QT_MOC_LITERAL(5, 47, 15), // "selectMediafile"
QT_MOC_LITERAL(6, 63, 16), // "addMediainfoForm"
QT_MOC_LITERAL(7, 80, 10), // "setFFprobe"
QT_MOC_LITERAL(8, 91, 7), // "a_state"
QT_MOC_LITERAL(9, 99, 7), // "setFull"
QT_MOC_LITERAL(10, 107, 10), // "setWrapped"
QT_MOC_LITERAL(11, 118, 8), // "a_enable"
QT_MOC_LITERAL(12, 127, 7), // "calcMd5"
QT_MOC_LITERAL(13, 135, 43), // "on_editMediaInfo_customContex..."
QT_MOC_LITERAL(14, 179, 5), // "a_pos"
QT_MOC_LITERAL(15, 185, 30), // "on_buttonMediaInfoSave_clicked"
QT_MOC_LITERAL(16, 216, 30), // "on_buttonMediaInfoCopy_clicked"
QT_MOC_LITERAL(17, 247, 37), // "on_checkBoxMediaInfoFull_stat..."
QT_MOC_LITERAL(18, 285, 33), // "on_buttonMediaInfoPreview_cli..."
QT_MOC_LITERAL(19, 319, 14), // "dragEnterEvent"
QT_MOC_LITERAL(20, 334, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(21, 351, 1), // "e"
QT_MOC_LITERAL(22, 353, 9), // "dropEvent"
QT_MOC_LITERAL(23, 363, 11), // "QDropEvent*"
QT_MOC_LITERAL(24, 375, 10), // "closeEvent"
QT_MOC_LITERAL(25, 386, 12), // "QCloseEvent*"
QT_MOC_LITERAL(26, 399, 36), // "slotSubProcessReadyReadStanda..."
QT_MOC_LITERAL(27, 436, 37) // "slotSubProcessReadyReadStanda..."

    },
    "MediaInfoDialog\0reload\0\0a_filename\0"
    "slotPreview\0selectMediafile\0"
    "addMediainfoForm\0setFFprobe\0a_state\0"
    "setFull\0setWrapped\0a_enable\0calcMd5\0"
    "on_editMediaInfo_customContextMenuRequested\0"
    "a_pos\0on_buttonMediaInfoSave_clicked\0"
    "on_buttonMediaInfoCopy_clicked\0"
    "on_checkBoxMediaInfoFull_stateChanged\0"
    "on_buttonMediaInfoPreview_clicked\0"
    "dragEnterEvent\0QDragEnterEvent*\0e\0"
    "dropEvent\0QDropEvent*\0closeEvent\0"
    "QCloseEvent*\0slotSubProcessReadyReadStandardError\0"
    "slotSubProcessReadyReadStandardOutput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MediaInfoDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x08 /* Private */,
       1,    0,  112,    2, 0x08 /* Private */,
       4,    0,  113,    2, 0x08 /* Private */,
       5,    0,  114,    2, 0x08 /* Private */,
       6,    0,  115,    2, 0x08 /* Private */,
       7,    1,  116,    2, 0x08 /* Private */,
       9,    1,  119,    2, 0x08 /* Private */,
      10,    1,  122,    2, 0x08 /* Private */,
      12,    0,  125,    2, 0x08 /* Private */,
      13,    1,  126,    2, 0x08 /* Private */,
      15,    0,  129,    2, 0x08 /* Private */,
      16,    0,  130,    2, 0x08 /* Private */,
      17,    1,  131,    2, 0x08 /* Private */,
      18,    0,  134,    2, 0x08 /* Private */,
      19,    1,  135,    2, 0x09 /* Protected */,
      22,    1,  138,    2, 0x09 /* Protected */,
      24,    1,  141,    2, 0x09 /* Protected */,
      26,    0,  144,    2, 0x09 /* Protected */,
      27,    0,  145,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23,   21,
    QMetaType::Void, 0x80000000 | 25,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MediaInfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaInfoDialog *_t = static_cast<MediaInfoDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->reload(); break;
        case 2: _t->slotPreview(); break;
        case 3: _t->selectMediafile(); break;
        case 4: _t->addMediainfoForm(); break;
        case 5: _t->setFFprobe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setFull((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setWrapped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->calcMd5(); break;
        case 9: _t->on_editMediaInfo_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: _t->on_buttonMediaInfoSave_clicked(); break;
        case 11: _t->on_buttonMediaInfoCopy_clicked(); break;
        case 12: _t->on_checkBoxMediaInfoFull_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_buttonMediaInfoPreview_clicked(); break;
        case 14: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 15: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 16: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 17: _t->slotSubProcessReadyReadStandardError(); break;
        case 18: _t->slotSubProcessReadyReadStandardOutput(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MediaInfoDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MediaInfoDialog.data,
      qt_meta_data_MediaInfoDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MediaInfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MediaInfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MediaInfoDialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MediaInfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
