/****************************************************************************
** Meta object code from reading C++ file 'qxtpushbutton.h'
**
** Created: Mon May 3 17:55:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtpushbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtpushbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtPushButton[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      28,   14, 0x0009510b,
      52,   37, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_QxtPushButton[] = {
    "QxtPushButton\0Qxt::Rotation\0rotation\0"
    "Qt::TextFormat\0textFormat\0"
};

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtPushButton[] = {
        Qxt::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtPushButton[] = {
        &Qxt::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

static const QMetaObjectExtraData qt_meta_extradata2_QxtPushButton = {
    qt_meta_extradata_QxtPushButton, 0 
};

const QMetaObject QxtPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_QxtPushButton,
      qt_meta_data_QxtPushButton, &qt_meta_extradata2_QxtPushButton }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtPushButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtPushButton))
        return static_cast<void*>(const_cast< QxtPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int QxtPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Qxt::Rotation*>(_v) = rotation(); break;
        case 1: *reinterpret_cast< Qt::TextFormat*>(_v) = textFormat(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRotation(*reinterpret_cast< Qxt::Rotation*>(_v)); break;
        case 1: setTextFormat(*reinterpret_cast< Qt::TextFormat*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
