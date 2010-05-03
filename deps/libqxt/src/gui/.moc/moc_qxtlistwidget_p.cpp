/****************************************************************************
** Meta object code from reading C++ file 'qxtlistwidget_p.h'
**
** Created: Mon May 3 17:55:09 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtlistwidget_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtlistwidget_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtListWidgetPrivate[] = {

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
      28,   22,   21,   21, 0x08,
      60,   22,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QxtListWidgetPrivate[] = {
    "QxtListWidgetPrivate\0\0index\0"
    "informStartEditing(QModelIndex)\0"
    "informFinishEditing(QModelIndex)\0"
};

const QMetaObject QxtListWidgetPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtListWidgetPrivate,
      qt_meta_data_QxtListWidgetPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtListWidgetPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtListWidgetPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtListWidgetPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtListWidgetPrivate))
        return static_cast<void*>(const_cast< QxtListWidgetPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtListWidget>"))
        return static_cast< QxtPrivate<QxtListWidget>*>(const_cast< QxtListWidgetPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtListWidgetPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: informStartEditing((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: informFinishEditing((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
