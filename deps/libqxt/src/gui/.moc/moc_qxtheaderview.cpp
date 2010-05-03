/****************************************************************************
** Meta object code from reading C++ file 'qxtheaderview.h'
**
** Created: Mon May 3 17:55:05 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtheaderview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtheaderview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtHeaderView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      19,   14, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtHeaderView[] = {
    "QxtHeaderView\0bool\0proportionalSectionSizes\0"
};

const QMetaObject QxtHeaderView::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_QxtHeaderView,
      qt_meta_data_QxtHeaderView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtHeaderView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtHeaderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtHeaderView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtHeaderView))
        return static_cast<void*>(const_cast< QxtHeaderView*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int QxtHeaderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = hasProportionalSectionSizes(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setProportionalSectionSizes(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
