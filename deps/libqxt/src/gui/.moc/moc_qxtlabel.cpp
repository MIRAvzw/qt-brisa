/****************************************************************************
** Meta object code from reading C++ file 'qxtlabel.h'
**
** Created: Mon May 3 17:55:07 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtlabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtLabel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       4,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      25,   20,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   20,    9,    9, 0x0a,

 // properties: name, type, flags
      20,   63, 0x0a095103,
      85,   71, 0x0009510b,
     113,   95, 0x0009510b,
     137,  123, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_QxtLabel[] = {
    "QxtLabel\0\0clicked()\0text\0textChanged(QString)\0"
    "setText(QString)\0QString\0Qt::Alignment\0"
    "alignment\0Qt::TextElideMode\0elideMode\0"
    "Qxt::Rotation\0rotation\0"
};

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtLabel[] = {
        Qxt::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtLabel[] = {
        &Qxt::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

static const QMetaObjectExtraData qt_meta_extradata2_QxtLabel = {
    qt_meta_extradata_QxtLabel, 0 
};

const QMetaObject QxtLabel::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QxtLabel,
      qt_meta_data_QxtLabel, &qt_meta_extradata2_QxtLabel }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtLabel))
        return static_cast<void*>(const_cast< QxtLabel*>(this));
    return QFrame::qt_metacast(_clname);
}

int QxtLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = text(); break;
        case 1: *reinterpret_cast< Qt::Alignment*>(_v) = alignment(); break;
        case 2: *reinterpret_cast< Qt::TextElideMode*>(_v) = elideMode(); break;
        case 3: *reinterpret_cast< Qxt::Rotation*>(_v) = rotation(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: setAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 2: setElideMode(*reinterpret_cast< Qt::TextElideMode*>(_v)); break;
        case 3: setRotation(*reinterpret_cast< Qxt::Rotation*>(_v)); break;
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
void QxtLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QxtLabel::textChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
