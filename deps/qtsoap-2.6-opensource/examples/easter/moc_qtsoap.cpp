/****************************************************************************
** Meta object code from reading C++ file 'qtsoap.h'
**
** Created: Mon Feb 22 14:23:48 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qtsoap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtsoap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtSoapHttpTransport[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   37,   20,   20, 0x08,
      74,   69,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtSoapHttpTransport[] = {
    "QtSoapHttpTransport\0\0responseReady()\0"
    "id,error\0readResponse(int,bool)\0resp\0"
    "readResponseHeader(QHttpResponseHeader)\0"
};

const QMetaObject QtSoapHttpTransport::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtSoapHttpTransport,
      qt_meta_data_QtSoapHttpTransport, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtSoapHttpTransport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtSoapHttpTransport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtSoapHttpTransport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSoapHttpTransport))
        return static_cast<void*>(const_cast< QtSoapHttpTransport*>(this));
    return QObject::qt_metacast(_clname);
}

int QtSoapHttpTransport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: responseReady(); break;
        case 1: readResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: readResponseHeader((*reinterpret_cast< const QHttpResponseHeader(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QtSoapHttpTransport::responseReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
