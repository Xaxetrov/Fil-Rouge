/****************************************************************************
** Meta object code from reading C++ file 'WorldWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WorldWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WorldWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WorldWidget_t {
    QByteArrayData data[9];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorldWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorldWidget_t qt_meta_stringdata_WorldWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WorldWidget"
QT_MOC_LITERAL(1, 12, 11), // "updateScene"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "resizeEvent"
QT_MOC_LITERAL(4, 37, 13), // "QResizeEvent*"
QT_MOC_LITERAL(5, 51, 1), // "e"
QT_MOC_LITERAL(6, 53, 4), // "tick"
QT_MOC_LITERAL(7, 58, 15), // "startSimulation"
QT_MOC_LITERAL(8, 74, 17) // "suspendSimulation"

    },
    "WorldWidget\0updateScene\0\0resizeEvent\0"
    "QResizeEvent*\0e\0tick\0startSimulation\0"
    "suspendSimulation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorldWidget[] = {

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
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WorldWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorldWidget *_t = static_cast<WorldWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateScene(); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 2: _t->tick(); break;
        case 3: _t->startSimulation(); break;
        case 4: _t->suspendSimulation(); break;
        default: ;
        }
    }
}

const QMetaObject WorldWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_WorldWidget.data,
      qt_meta_data_WorldWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorldWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorldWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorldWidget.stringdata0))
        return static_cast<void*>(const_cast< WorldWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int WorldWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
