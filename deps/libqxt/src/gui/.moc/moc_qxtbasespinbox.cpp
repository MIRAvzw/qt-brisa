/****************************************************************************
** Meta object code from reading C++ file 'qxtbasespinbox.h'
**
** Created: Mon May 3 17:54:54 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtbasespinbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtbasespinbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtBaseSpinBox[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   16,   15,   15, 0x0a,

 // properties: name, type, flags
      16,   51, 0x02095103,
      60,   55, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtBaseSpinBox[] = {
    "QxtBaseSpinBox\0\0base\0baseChanged(int)\0"
    "setBase(int)\0int\0bool\0upperCase\0"
};

const QMetaObject QxtBaseSpinBox::staticMetaObject = {
    { &QSpinBox::staticMetaObject, qt_meta_stringdata_QxtBaseSpinBox,
      qt_meta_data_QxtBaseSpinBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtBaseSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtBaseSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtBaseSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtBaseSpinBox))
        return static_cast<void*>(const_cast< QxtBaseSpinBox*>(this));
    return QSpinBox::qt_metacast(_clname);
}

int QxtBaseSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: baseChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setBase((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = base(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isUpperCase(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBase(*reinterpret_cast< int*>(_v)); break;
        case 1: setUpperCase(*reinterpret_cast< bool*>(_v)); break;
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

// SIGNAL 0
void QxtBaseSpinBox::baseChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
