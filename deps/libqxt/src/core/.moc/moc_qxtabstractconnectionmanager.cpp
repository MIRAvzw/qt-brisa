/****************************************************************************
** Meta object code from reading C++ file 'qxtabstractconnectionmanager.h'
**
** Created: Mon May 3 17:54:05 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtabstractconnectionmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtabstractconnectionmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtAbstractConnectionManager[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      46,   30,   29,   29, 0x05,
      80,   30,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
     122,  113,   29,   29, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtAbstractConnectionManager[] = {
    "QxtAbstractConnectionManager\0\0"
    "device,clientID\0newConnection(QIODevice*,quint64)\0"
    "disconnected(QIODevice*,quint64)\0"
    "clientID\0disconnect(quint64)\0"
};

const QMetaObject QxtAbstractConnectionManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtAbstractConnectionManager,
      qt_meta_data_QxtAbstractConnectionManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtAbstractConnectionManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtAbstractConnectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtAbstractConnectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtAbstractConnectionManager))
        return static_cast<void*>(const_cast< QxtAbstractConnectionManager*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtAbstractConnectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newConnection((*reinterpret_cast< QIODevice*(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 1: disconnected((*reinterpret_cast< QIODevice*(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 2: disconnect((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QxtAbstractConnectionManager::newConnection(QIODevice * _t1, quint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtAbstractConnectionManager::disconnected(QIODevice * _t1, quint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
