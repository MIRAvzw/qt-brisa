/****************************************************************************
** Meta object code from reading C++ file 'google.h'
**
** Created: Mon Feb 22 14:23:41 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "google.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'google.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Google[] = {

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
       8,    7,    7,    7, 0x08,
      24,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Google[] = {
    "Google\0\0submitRequest()\0getResponse()\0"
};

const QMetaObject Google::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Google,
      qt_meta_data_Google, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Google::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Google::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Google::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Google))
        return static_cast<void*>(const_cast< Google*>(this));
    return QWidget::qt_metacast(_clname);
}

int Google::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: submitRequest(); break;
        case 1: getResponse(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
