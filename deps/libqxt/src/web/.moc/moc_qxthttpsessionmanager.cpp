/****************************************************************************
** Meta object code from reading C++ file 'qxthttpsessionmanager.h'
**
** Created: Mon May 3 17:56:03 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxthttpsessionmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxthttpsessionmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtHttpSessionManager[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      49,   39,   22,   22, 0x08,
      91,   70,   22,   22, 0x08,
     120,   70,   22,   22, 0x08,
     148,   70,   22,   22, 0x08,
     177,   70,   22,   22, 0x08,
     206,   70,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtHttpSessionManager[] = {
    "QxtHttpSessionManager\0\0processEvents()\0"
    "requestID\0closeConnection(int)\0"
    "requestID,dataSource\0chunkReadyRead(int,QObject*)\0"
    "sendNextChunk(int,QObject*)\0"
    "sendEmptyChunk(int,QObject*)\0"
    "blockReadyRead(int,QObject*)\0"
    "sendNextBlock(int,QObject*)\0"
};

const QMetaObject QxtHttpSessionManager::staticMetaObject = {
    { &QxtAbstractWebSessionManager::staticMetaObject, qt_meta_stringdata_QxtHttpSessionManager,
      qt_meta_data_QxtHttpSessionManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtHttpSessionManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtHttpSessionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtHttpSessionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtHttpSessionManager))
        return static_cast<void*>(const_cast< QxtHttpSessionManager*>(this));
    return QxtAbstractWebSessionManager::qt_metacast(_clname);
}

int QxtHttpSessionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QxtAbstractWebSessionManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: processEvents(); break;
        case 1: closeConnection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: chunkReadyRead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 3: sendNextChunk((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 4: sendEmptyChunk((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 5: blockReadyRead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 6: sendNextBlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
