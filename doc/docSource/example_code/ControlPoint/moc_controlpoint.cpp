/****************************************************************************
** Meta object code from reading C++ file 'controlpoint.h'
**
** Created: Tue Feb 23 16:43:11 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controlpoint.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HandleCmds[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      20,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,
      36,   34,   11,   11, 0x05,
      50,   11,   11,   11, 0x05,
      59,   11,   11,   11, 0x05,
      69,   11,   11,   11, 0x05,
      81,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_HandleCmds[] = {
    "HandleCmds\0\0leave()\0list()\0help()\0i\0"
    "setLight(int)\0turnOn()\0turnOff()\0"
    "getTarget()\0getStatus()\0"
};

const QMetaObject HandleCmds::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_HandleCmds,
      qt_meta_data_HandleCmds, 0 }
};

const QMetaObject *HandleCmds::metaObject() const
{
    return &staticMetaObject;
}

void *HandleCmds::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HandleCmds))
        return static_cast<void*>(const_cast< HandleCmds*>(this));
    return QThread::qt_metacast(_clname);
}

int HandleCmds::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: leave(); break;
        case 1: list(); break;
        case 2: help(); break;
        case 3: setLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: turnOn(); break;
        case 5: turnOff(); break;
        case 6: getTarget(); break;
        case 7: getStatus(); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void HandleCmds::leave()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HandleCmds::list()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HandleCmds::help()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HandleCmds::setLight(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void HandleCmds::turnOn()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HandleCmds::turnOff()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HandleCmds::getTarget()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void HandleCmds::getStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
static const uint qt_meta_data_ControlPoint[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      27,   21,   13,   13, 0x08,
      41,   13,   13,   13, 0x08,
      53,   13,   13,   13, 0x08,
      65,   13,   13,   13, 0x08,
      74,   13,   13,   13, 0x08,
      84,   13,   13,   13, 0x08,
      91,   13,   13,   13, 0x08,
     114,   98,   13,   13, 0x08,
     149,   98,   13,   13, 0x08,
     184,   98,   13,   13, 0x08,
     223,  219,   13,   13, 0x08,
     266,  261,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlPoint[] = {
    "ControlPoint\0\0help()\0index\0setLight(int)\0"
    "getTarget()\0getStatus()\0turnOn()\0"
    "turnOff()\0exit()\0list()\0response,method\0"
    "setTargetResponse(QString,QString)\0"
    "getTargetResponse(QString,QString)\0"
    "getStatusResponse(QString,QString)\0"
    "dev\0onNewDevice(BrisaControlPointDevice*)\0"
    "desc\0onRemovedDevice(QString)\0"
};

const QMetaObject ControlPoint::staticMetaObject = {
    { &BrisaControlPoint::staticMetaObject, qt_meta_stringdata_ControlPoint,
      qt_meta_data_ControlPoint, 0 }
};

const QMetaObject *ControlPoint::metaObject() const
{
    return &staticMetaObject;
}

void *ControlPoint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPoint))
        return static_cast<void*>(const_cast< ControlPoint*>(this));
    return BrisaControlPoint::qt_metacast(_clname);
}

int ControlPoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BrisaControlPoint::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: help(); break;
        case 1: setLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: getTarget(); break;
        case 3: getStatus(); break;
        case 4: turnOn(); break;
        case 5: turnOff(); break;
        case 6: exit(); break;
        case 7: list(); break;
        case 8: setTargetResponse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: getTargetResponse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: getStatusResponse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: onNewDevice((*reinterpret_cast< BrisaControlPointDevice*(*)>(_a[1]))); break;
        case 12: onRemovedDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
