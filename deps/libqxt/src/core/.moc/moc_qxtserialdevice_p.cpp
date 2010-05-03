/****************************************************************************
** Meta object code from reading C++ file 'qxtserialdevice_p.h'
**
** Created: Mon May 3 17:54:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtserialdevice_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtserialdevice_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSerialDevicePrivate[] = {

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
      28,   23,   24,   23, 0x0a,
      41,   23,   24,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtSerialDevicePrivate[] = {
    "QxtSerialDevicePrivate\0\0int\0fillBuffer()\0"
    "constFillBuffer()\0"
};

const QMetaObject QxtSerialDevicePrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtSerialDevicePrivate,
      qt_meta_data_QxtSerialDevicePrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSerialDevicePrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSerialDevicePrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSerialDevicePrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSerialDevicePrivate))
        return static_cast<void*>(const_cast< QxtSerialDevicePrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtSerialDevice>"))
        return static_cast< QxtPrivate<QxtSerialDevice>*>(const_cast< QxtSerialDevicePrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtSerialDevicePrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = fillBuffer();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = constFillBuffer();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
