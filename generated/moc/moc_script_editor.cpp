/****************************************************************************
** Meta object code from reading C++ file 'script_editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../script/script_editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'script_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScriptEditor_t {
    QByteArrayData data[6];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScriptEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScriptEditor_t qt_meta_stringdata_ScriptEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ScriptEditor"
QT_MOC_LITERAL(1, 13, 25), // "updateLineNumberAreaWidth"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "newBlockCount"
QT_MOC_LITERAL(4, 54, 20), // "highlightCurrentLine"
QT_MOC_LITERAL(5, 75, 20) // "updateLineNumberArea"

    },
    "ScriptEditor\0updateLineNumberAreaWidth\0"
    "\0newBlockCount\0highlightCurrentLine\0"
    "updateLineNumberArea"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScriptEditor[] = {

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
       5,    2,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    2,

       0        // eod
};

void ScriptEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScriptEditor *_t = static_cast<ScriptEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->highlightCurrentLine(); break;
        case 2: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScriptEditor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_ScriptEditor.data,
      qt_meta_data_ScriptEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScriptEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScriptEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptEditor.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int ScriptEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
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
