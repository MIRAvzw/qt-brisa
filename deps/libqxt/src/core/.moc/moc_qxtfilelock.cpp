/****************************************************************************
** Meta object code from reading C++ file 'qxtfilelock.h'
**
** Created: Mon May 3 17:54:07 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtfilelock.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtfilelock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtFileLock[] = {

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
      18,   12,   13,   12, 0x0a,
      25,   12,   13,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtFileLock[] = {
    "QxtFileLock\0\0bool\0lock()\0unlock()\0"
};

const QMetaObject QxtFileLock::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtFileLock,
      qt_meta_data_QxtFileLock, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtFileLock::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtFileLock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtFileLock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtFileLock))
        return static_cast<void*>(const_cast< QxtFileLock*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtFileLock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = lock();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = unlock();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
