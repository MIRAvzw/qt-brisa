/****************************************************************************
** Meta object code from reading C++ file 'qxtconfigdialog_p.h'
**
** Created: Mon May 3 17:54:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtconfigdialog_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtconfigdialog_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtConfigDialogPrivate[] = {

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
      35,   24,   23,   23, 0x0a,
      66,   60,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtConfigDialogPrivate[] = {
    "QxtConfigDialogPrivate\0\0row,column\0"
    "setCurrentIndex(int,int)\0index\0"
    "setCurrentIndex(int)\0"
};

const QMetaObject QxtConfigDialogPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtConfigDialogPrivate,
      qt_meta_data_QxtConfigDialogPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtConfigDialogPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtConfigDialogPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtConfigDialogPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtConfigDialogPrivate))
        return static_cast<void*>(const_cast< QxtConfigDialogPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtConfigDialog>"))
        return static_cast< QxtPrivate<QxtConfigDialog>*>(const_cast< QxtConfigDialogPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtConfigDialogPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCurrentIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
