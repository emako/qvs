/****************************************************************************
** Meta object code from reading C++ file 'timeline_slider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../preview/timeline_slider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeline_slider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimeLineSlider_t {
    QByteArrayData data[19];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimeLineSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimeLineSlider_t qt_meta_stringdata_TimeLineSlider = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TimeLineSlider"
QT_MOC_LITERAL(1, 15, 17), // "signalSliderMoved"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "a_frame"
QT_MOC_LITERAL(4, 42, 18), // "signalFrameChanged"
QT_MOC_LITERAL(5, 61, 19), // "signalSliderPressed"
QT_MOC_LITERAL(6, 81, 20), // "signalSliderReleased"
QT_MOC_LITERAL(7, 102, 10), // "slotStepUp"
QT_MOC_LITERAL(8, 113, 12), // "slotStepDown"
QT_MOC_LITERAL(9, 126, 13), // "slotBigStepUp"
QT_MOC_LITERAL(10, 140, 15), // "slotBigStepDown"
QT_MOC_LITERAL(11, 156, 10), // "slotStepBy"
QT_MOC_LITERAL(12, 167, 6), // "a_step"
QT_MOC_LITERAL(13, 174, 17), // "slotStepBySeconds"
QT_MOC_LITERAL(14, 192, 9), // "a_seconds"
QT_MOC_LITERAL(15, 202, 24), // "slotBookmarkCurrentFrame"
QT_MOC_LITERAL(16, 227, 26), // "slotUnbookmarkCurrentFrame"
QT_MOC_LITERAL(17, 254, 24), // "slotGoToPreviousBookmark"
QT_MOC_LITERAL(18, 279, 20) // "slotGoToNextBookmark"

    },
    "TimeLineSlider\0signalSliderMoved\0\0"
    "a_frame\0signalFrameChanged\0"
    "signalSliderPressed\0signalSliderReleased\0"
    "slotStepUp\0slotStepDown\0slotBigStepUp\0"
    "slotBigStepDown\0slotStepBy\0a_step\0"
    "slotStepBySeconds\0a_seconds\0"
    "slotBookmarkCurrentFrame\0"
    "slotUnbookmarkCurrentFrame\0"
    "slotGoToPreviousBookmark\0slotGoToNextBookmark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimeLineSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    0,   90,    2, 0x06 /* Public */,
       6,    0,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   92,    2, 0x0a /* Public */,
       8,    0,   93,    2, 0x0a /* Public */,
       9,    0,   94,    2, 0x0a /* Public */,
      10,    0,   95,    2, 0x0a /* Public */,
      11,    1,   96,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TimeLineSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TimeLineSlider *_t = static_cast<TimeLineSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalFrameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSliderPressed(); break;
        case 3: _t->signalSliderReleased(); break;
        case 4: _t->slotStepUp(); break;
        case 5: _t->slotStepDown(); break;
        case 6: _t->slotBigStepUp(); break;
        case 7: _t->slotBigStepDown(); break;
        case 8: _t->slotStepBy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotStepBySeconds((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->slotBookmarkCurrentFrame(); break;
        case 11: _t->slotUnbookmarkCurrentFrame(); break;
        case 12: _t->slotGoToPreviousBookmark(); break;
        case 13: _t->slotGoToNextBookmark(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimeLineSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineSlider::signalSliderMoved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimeLineSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineSlider::signalFrameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TimeLineSlider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineSlider::signalSliderPressed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TimeLineSlider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineSlider::signalSliderReleased)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TimeLineSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TimeLineSlider.data,
      qt_meta_data_TimeLineSlider,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TimeLineSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimeLineSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimeLineSlider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TimeLineSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TimeLineSlider::signalSliderMoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TimeLineSlider::signalFrameChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TimeLineSlider::signalSliderPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TimeLineSlider::signalSliderReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
