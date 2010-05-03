/****************************************************************************
** Meta object code from reading C++ file 'qxtgroupbox.h'
**
** Created: Mon May 3 17:55:04 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtgroupbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtgroupbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtGroupBox[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x0a,
      42,   12,   12,   12, 0x2a,
      66,   57,   12,   12, 0x0a,
      84,   12,   12,   12, 0x2a,

 // properties: name, type, flags
     103,   98, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtGroupBox[] = {
    "QxtGroupBox\0\0collapsed\0setCollapsed(bool)\0"
    "setCollapsed()\0expanded\0setExpanded(bool)\0"
    "setExpanded()\0bool\0collapsive\0"
};

const QMetaObject QxtGroupBox::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_QxtGroupBox,
      qt_meta_data_QxtGroupBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtGroupBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtGroupBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtGroupBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtGroupBox))
        return static_cast<void*>(const_cast< QxtGroupBox*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int QxtGroupBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCollapsed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setCollapsed(); break;
        case 2: setExpanded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setExpanded(); break;
        default: ;
        }
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isCollapsive(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setCollapsive(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
