/****************************************************************************
** Meta object code from reading C++ file 'syntax_highlighter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../script/syntax_highlighter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'syntax_highlighter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SyntaxHighlighter_t {
    QByteArrayData data[14];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SyntaxHighlighter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SyntaxHighlighter_t qt_meta_stringdata_SyntaxHighlighter = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SyntaxHighlighter"
QT_MOC_LITERAL(1, 18, 5), // "setup"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "clear"
QT_MOC_LITERAL(4, 31, 17), // "addSyntaxKeywords"
QT_MOC_LITERAL(5, 49, 10), // "a_keywords"
QT_MOC_LITERAL(6, 60, 15), // "QTextCharFormat"
QT_MOC_LITERAL(7, 76, 8), // "a_format"
QT_MOC_LITERAL(8, 85, 16), // "addSyntaxComment"
QT_MOC_LITERAL(9, 102, 13), // "ECOMMENT_TYPE"
QT_MOC_LITERAL(10, 116, 6), // "a_type"
QT_MOC_LITERAL(11, 123, 17), // "addSyntaxFunction"
QT_MOC_LITERAL(12, 141, 9), // "addSyntax"
QT_MOC_LITERAL(13, 151, 9) // "a_pattern"

    },
    "SyntaxHighlighter\0setup\0\0clear\0"
    "addSyntaxKeywords\0a_keywords\0"
    "QTextCharFormat\0a_format\0addSyntaxComment\0"
    "ECOMMENT_TYPE\0a_type\0addSyntaxFunction\0"
    "addSyntax\0a_pattern"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyntaxHighlighter[] = {

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
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    2,   66,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x2a /* Public | MethodCloned */,
       8,    2,   74,    2, 0x0a /* Public */,
       8,    1,   79,    2, 0x2a /* Public | MethodCloned */,
       8,    0,   82,    2, 0x2a /* Public | MethodCloned */,
      11,    1,   83,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x2a /* Public | MethodCloned */,
      12,    2,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 6,   10,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 6,   13,    7,

       0        // eod
};

void SyntaxHighlighter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SyntaxHighlighter *_t = static_cast<SyntaxHighlighter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setup(); break;
        case 1: _t->clear(); break;
        case 2: _t->addSyntaxKeywords((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QTextCharFormat(*)>(_a[2]))); break;
        case 3: _t->addSyntaxKeywords((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 4: _t->addSyntaxComment((*reinterpret_cast< const ECOMMENT_TYPE(*)>(_a[1])),(*reinterpret_cast< const QTextCharFormat(*)>(_a[2]))); break;
        case 5: _t->addSyntaxComment((*reinterpret_cast< const ECOMMENT_TYPE(*)>(_a[1]))); break;
        case 6: _t->addSyntaxComment(); break;
        case 7: _t->addSyntaxFunction((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 8: _t->addSyntaxFunction(); break;
        case 9: _t->addSyntax((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QTextCharFormat(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SyntaxHighlighter::staticMetaObject = {
    { &QSyntaxHighlighter::staticMetaObject, qt_meta_stringdata_SyntaxHighlighter.data,
      qt_meta_data_SyntaxHighlighter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SyntaxHighlighter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyntaxHighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SyntaxHighlighter.stringdata0))
        return static_cast<void*>(this);
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int SyntaxHighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
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
