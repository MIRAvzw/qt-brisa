/****************************************************************************
** Meta object code from reading C++ file 'qxtcheckcombobox.h'
**
** Created: Mon May 3 17:54:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtcheckcombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtcheckcombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtCheckComboBox[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       3,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   18,   17,   17, 0x0a,

 // properties: name, type, flags
      94,   86, 0x0a095103,
     104,   86, 0x0a095103,
     128,  116, 0x0b095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtCheckComboBox[] = {
    "QxtCheckComboBox\0\0items\0"
    "checkedItemsChanged(QStringList)\0"
    "setCheckedItems(QStringList)\0QString\0"
    "separator\0defaultText\0QStringList\0"
    "checkedItems\0"
};

const QMetaObject QxtCheckComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_QxtCheckComboBox,
      qt_meta_data_QxtCheckComboBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtCheckComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtCheckComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtCheckComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtCheckComboBox))
        return static_cast<void*>(const_cast< QxtCheckComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int QxtCheckComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkedItemsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: setCheckedItems((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = separator(); break;
        case 1: *reinterpret_cast< QString*>(_v) = defaultText(); break;
        case 2: *reinterpret_cast< QStringList*>(_v) = checkedItems(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSeparator(*reinterpret_cast< QString*>(_v)); break;
        case 1: setDefaultText(*reinterpret_cast< QString*>(_v)); break;
        case 2: setCheckedItems(*reinterpret_cast< QStringList*>(_v)); break;
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

// SIGNAL 0
void QxtCheckComboBox::checkedItemsChanged(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
