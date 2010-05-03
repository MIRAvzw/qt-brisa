/****************************************************************************
** Meta object code from reading C++ file 'qxtsignalgroup.h'
**
** Created: Mon May 3 17:54:14 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtsignalgroup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtsignalgroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSignalGroup[] = {

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
      16,   15,   15,   15, 0x05,
      38,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtSignalGroup[] = {
    "QxtSignalGroup\0\0firstSignalReceived()\0"
    "allSignalsReceived()\0reset()\0"
};

const QMetaObject QxtSignalGroup::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtSignalGroup,
      qt_meta_data_QxtSignalGroup, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSignalGroup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSignalGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSignalGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSignalGroup))
        return static_cast<void*>(const_cast< QxtSignalGroup*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtSignalGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: firstSignalReceived(); break;
        case 1: allSignalsReceived(); break;
        case 2: reset(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QxtSignalGroup::firstSignalReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtSignalGroup::allSignalsReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
