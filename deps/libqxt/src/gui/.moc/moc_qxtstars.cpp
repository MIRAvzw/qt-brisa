/****************************************************************************
** Meta object code from reading C++ file 'qxtstars.h'
**
** Created: Mon May 3 17:55:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtstars.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtstars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtStars[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      14,    9, 0x01095103,
      29,   23, 0x15095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtStars[] = {
    "QxtStars\0bool\0readOnly\0QSize\0starSize\0"
};

const QMetaObject QxtStars::staticMetaObject = {
    { &QAbstractSlider::staticMetaObject, qt_meta_stringdata_QxtStars,
      qt_meta_data_QxtStars, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtStars::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtStars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtStars::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtStars))
        return static_cast<void*>(const_cast< QxtStars*>(this));
    return QAbstractSlider::qt_metacast(_clname);
}

int QxtStars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isReadOnly(); break;
        case 1: *reinterpret_cast< QSize*>(_v) = starSize(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setReadOnly(*reinterpret_cast< bool*>(_v)); break;
        case 1: setStarSize(*reinterpret_cast< QSize*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
