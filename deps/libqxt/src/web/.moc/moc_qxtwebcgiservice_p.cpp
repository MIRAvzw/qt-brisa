/****************************************************************************
** Meta object code from reading C++ file 'qxtwebcgiservice_p.h'
**
** Created: Mon May 3 17:56:05 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtwebcgiservice_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtwebcgiservice_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtWebCgiServicePrivate[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   25,   24,   24, 0x0a,
      62,   24,   24,   24, 0x2a,
      81,   24,   24,   24, 0x0a,
     100,   24,   24,   24, 0x0a,
     128,  118,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtWebCgiServicePrivate[] = {
    "QxtWebCgiServicePrivate\0\0o_content\0"
    "browserReadyRead(QObject*)\0"
    "browserReadyRead()\0processReadyRead()\0"
    "processFinished()\0o_process\0"
    "terminateProcess(QObject*)\0"
};

const QMetaObject QxtWebCgiServicePrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtWebCgiServicePrivate,
      qt_meta_data_QxtWebCgiServicePrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtWebCgiServicePrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtWebCgiServicePrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtWebCgiServicePrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtWebCgiServicePrivate))
        return static_cast<void*>(const_cast< QxtWebCgiServicePrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtWebCgiService>"))
        return static_cast< QxtPrivate<QxtWebCgiService>*>(const_cast< QxtWebCgiServicePrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtWebCgiServicePrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: browserReadyRead((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: browserReadyRead(); break;
        case 2: processReadyRead(); break;
        case 3: processFinished(); break;
        case 4: terminateProcess((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
