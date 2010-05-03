/****************************************************************************
** Meta object code from reading C++ file 'qxtslotjob.h'
**
** Created: Mon May 3 17:54:14 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtslotjob.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtslotjob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtFuture[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      18,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QxtFuture[] = {
    "QxtFuture\0\0done()\0done(QVariant)\0"
};

const QMetaObject QxtFuture::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtFuture,
      qt_meta_data_QxtFuture, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtFuture::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtFuture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtFuture::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtFuture))
        return static_cast<void*>(const_cast< QxtFuture*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtFuture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: done(); break;
        case 1: done((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QxtFuture::done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtFuture::done(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QxtSlotJob[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtSlotJob[] = {
    "QxtSlotJob\0\0done(QVariant)\0pdone()\0"
};

const QMetaObject QxtSlotJob::staticMetaObject = {
    { &QxtJob::staticMetaObject, qt_meta_stringdata_QxtSlotJob,
      qt_meta_data_QxtSlotJob, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSlotJob::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSlotJob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSlotJob::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSlotJob))
        return static_cast<void*>(const_cast< QxtSlotJob*>(this));
    return QxtJob::qt_metacast(_clname);
}

int QxtSlotJob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QxtJob::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: done((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: pdone(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QxtSlotJob::done(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
