/****************************************************************************
** Meta object code from reading C++ file 'qxtscheduleview_p.h'
**
** Created: Mon May 3 17:55:22 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtscheduleview_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtscheduleview_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtScheduleInternalItem[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   25,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleInternalItem[] = {
    "QxtScheduleInternalItem\0\0item,oldGeometry\0"
    "geometryChanged(QxtScheduleInternalItem*,QVector<QRect>)\0"
};

const QMetaObject QxtScheduleInternalItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtScheduleInternalItem,
      qt_meta_data_QxtScheduleInternalItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleInternalItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleInternalItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleInternalItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleInternalItem))
        return static_cast<void*>(const_cast< QxtScheduleInternalItem*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtScheduleInternalItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: geometryChanged((*reinterpret_cast< QxtScheduleInternalItem*(*)>(_a[1])),(*reinterpret_cast< QVector<QRect>(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QxtScheduleInternalItem::geometryChanged(QxtScheduleInternalItem * _t1, QVector<QRect> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QxtScheduleViewPrivate[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   24,   23,   23, 0x0a,
     102,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleViewPrivate[] = {
    "QxtScheduleViewPrivate\0\0item,oldGeometry\0"
    "itemGeometryChanged(QxtScheduleInternalItem*,QVector<QRect>)\0"
    "scrollTimerTimeout()\0"
};

const QMetaObject QxtScheduleViewPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtScheduleViewPrivate,
      qt_meta_data_QxtScheduleViewPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleViewPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleViewPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleViewPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleViewPrivate))
        return static_cast<void*>(const_cast< QxtScheduleViewPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtScheduleView>"))
        return static_cast< QxtPrivate<QxtScheduleView>*>(const_cast< QxtScheduleViewPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtScheduleViewPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemGeometryChanged((*reinterpret_cast< QxtScheduleInternalItem*(*)>(_a[1])),(*reinterpret_cast< QVector<QRect>(*)>(_a[2]))); break;
        case 1: scrollTimerTimeout(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
