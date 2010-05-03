/****************************************************************************
** Meta object code from reading C++ file 'qxtitemdelegate.h'
**
** Created: Mon May 3 17:55:05 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtitemdelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtitemdelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtItemDelegate[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       4,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x05,
      51,   17,   16,   16, 0x05,

 // properties: name, type, flags
     101,   80, 0x0009510b,
     135,  117, 0x0009510b,
     153,  145, 0x0a095103,
     177,  172, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QxtItemDelegate[] = {
    "QxtItemDelegate\0\0index\0"
    "editingStarted(QModelIndex)\0"
    "editingFinished(QModelIndex)\0"
    "Qxt::DecorationStyle\0decorationStyle\0"
    "Qt::TextElideMode\0elideMode\0QString\0"
    "progressTextFormat\0bool\0progressTextVisible\0"
};

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtItemDelegate[] = {
        Qxt::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtItemDelegate[] = {
        &Qxt::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

static const QMetaObjectExtraData qt_meta_extradata2_QxtItemDelegate = {
    qt_meta_extradata_QxtItemDelegate, 0 
};

const QMetaObject QxtItemDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_QxtItemDelegate,
      qt_meta_data_QxtItemDelegate, &qt_meta_extradata2_QxtItemDelegate }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtItemDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtItemDelegate))
        return static_cast<void*>(const_cast< QxtItemDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int QxtItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editingStarted((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: editingFinished((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Qxt::DecorationStyle*>(_v) = decorationStyle(); break;
        case 1: *reinterpret_cast< Qt::TextElideMode*>(_v) = elideMode(); break;
        case 2: *reinterpret_cast< QString*>(_v) = progressTextFormat(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isProgressTextVisible(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDecorationStyle(*reinterpret_cast< Qxt::DecorationStyle*>(_v)); break;
        case 1: setElideMode(*reinterpret_cast< Qt::TextElideMode*>(_v)); break;
        case 2: setProgressTextFormat(*reinterpret_cast< QString*>(_v)); break;
        case 3: setProgressTextVisible(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QxtItemDelegate::editingStarted(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtItemDelegate::editingFinished(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
