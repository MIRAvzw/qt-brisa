/****************************************************************************
** Meta object code from reading C++ file 'qxtconfirmationmessage.h'
**
** Created: Mon May 3 17:54:58 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtconfirmationmessage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtconfirmationmessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtConfirmationMessage[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       5,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   23,   24,   23, 0x0a,
      35,   23,   23,   23, 0x0a,
      50,   43,   23,   23, 0x0a,

 // properties: name, type, flags
      68,   60, 0x0a095103,
      85,   60, 0x0a095103,
     113,   60, 0x0a095103,
     133,   60, 0x0a095103,
     167,  162, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtConfirmationMessage[] = {
    "QxtConfirmationMessage\0\0int\0exec()\0"
    "reset()\0result\0done(int)\0QString\0"
    "confirmationText\0overrideSettingsApplication\0"
    "overrideSettingsKey\0overrideSettingsOrganization\0"
    "bool\0rememberOnReject\0"
};

const QMetaObject QxtConfirmationMessage::staticMetaObject = {
    { &QMessageBox::staticMetaObject, qt_meta_stringdata_QxtConfirmationMessage,
      qt_meta_data_QxtConfirmationMessage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtConfirmationMessage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtConfirmationMessage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtConfirmationMessage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtConfirmationMessage))
        return static_cast<void*>(const_cast< QxtConfirmationMessage*>(this));
    return QMessageBox::qt_metacast(_clname);
}

int QxtConfirmationMessage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMessageBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: reset(); break;
        case 2: done((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = confirmationText(); break;
        case 1: *reinterpret_cast< QString*>(_v) = overrideSettingsApplication(); break;
        case 2: *reinterpret_cast< QString*>(_v) = overrideSettingsKey(); break;
        case 3: *reinterpret_cast< QString*>(_v) = overrideSettingsOrganization(); break;
        case 4: *reinterpret_cast< bool*>(_v) = rememberOnReject(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setConfirmationText(*reinterpret_cast< QString*>(_v)); break;
        case 1: setOverrideSettingsApplication(*reinterpret_cast< QString*>(_v)); break;
        case 2: setOverrideSettingsKey(*reinterpret_cast< QString*>(_v)); break;
        case 3: setOverrideSettingsOrganization(*reinterpret_cast< QString*>(_v)); break;
        case 4: setRememberOnReject(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
