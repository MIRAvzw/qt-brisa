/****************************************************************************
** Meta object code from reading C++ file 'qxtprogresslabel.h'
**
** Created: Mon May 3 17:55:11 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtprogresslabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtprogresslabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtProgressLabel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       3,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,
      38,   17,   17,   17, 0x0a,
      48,   17,   17,   17, 0x0a,
      64,   58,   17,   17, 0x0a,

 // properties: name, type, flags
      97,   89, 0x0a095103,
     111,   89, 0x0a095103,
     126,  122, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtProgressLabel[] = {
    "QxtProgressLabel\0\0value\0setValue(int)\0"
    "refresh()\0restart()\0event\0"
    "timerEvent(QTimerEvent*)\0QString\0"
    "contentFormat\0timeFormat\0int\0"
    "updateInterval\0"
};

const QMetaObject QxtProgressLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QxtProgressLabel,
      qt_meta_data_QxtProgressLabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtProgressLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtProgressLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtProgressLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtProgressLabel))
        return static_cast<void*>(const_cast< QxtProgressLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int QxtProgressLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: refresh(); break;
        case 2: restart(); break;
        case 3: timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = contentFormat(); break;
        case 1: *reinterpret_cast< QString*>(_v) = timeFormat(); break;
        case 2: *reinterpret_cast< int*>(_v) = updateInterval(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setContentFormat(*reinterpret_cast< QString*>(_v)); break;
        case 1: setTimeFormat(*reinterpret_cast< QString*>(_v)); break;
        case 2: setUpdateInterval(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
