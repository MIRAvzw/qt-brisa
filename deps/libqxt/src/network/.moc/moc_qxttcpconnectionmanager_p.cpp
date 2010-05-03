/****************************************************************************
** Meta object code from reading C++ file 'qxttcpconnectionmanager_p.h'
**
** Created: Mon May 3 17:55:47 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxttcpconnectionmanager_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxttcpconnectionmanager_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtTcpConnectionManagerPrivate[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   32,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtTcpConnectionManagerPrivate[] = {
    "QxtTcpConnectionManagerPrivate\0\0client\0"
    "socketDisconnected(QObject*)\0"
};

const QMetaObject QxtTcpConnectionManagerPrivate::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_QxtTcpConnectionManagerPrivate,
      qt_meta_data_QxtTcpConnectionManagerPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtTcpConnectionManagerPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtTcpConnectionManagerPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtTcpConnectionManagerPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtTcpConnectionManagerPrivate))
        return static_cast<void*>(const_cast< QxtTcpConnectionManagerPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtTcpConnectionManager>"))
        return static_cast< QxtPrivate<QxtTcpConnectionManager>*>(const_cast< QxtTcpConnectionManagerPrivate*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int QxtTcpConnectionManagerPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: socketDisconnected((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
