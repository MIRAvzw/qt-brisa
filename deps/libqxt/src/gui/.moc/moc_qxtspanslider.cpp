/****************************************************************************
** Meta object code from reading C++ file 'qxtspanslider.h'
**
** Created: Mon May 3 17:55:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtspanslider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtspanslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSpanSlider[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   64, // properties
       1,   79, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   15,   14,   14, 0x05,
      54,   48,   14,   14, 0x05,
      83,   77,   14,   14, 0x05,
     106,   48,   14,   14, 0x05,
     132,   77,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     158,   48,   14,   14, 0x0a,
     177,   77,   14,   14, 0x0a,
     196,   15,   14,   14, 0x0a,
     213,   48,   14,   14, 0x0a,
     235,   77,   14,   14, 0x0a,

 // properties: name, type, flags
     261,  257, 0x02095103,
     272,  257, 0x02095103,
     283,  257, 0x02095103,
     297,  257, 0x02095103,
     330,  311, 0x0009510b,

 // enums: name, flags, count, data
     311, 0x0,    3,   83,

 // enum data: key, value
     349, uint(QxtSpanSlider::FreeMovement),
     362, uint(QxtSpanSlider::NoCrossing),
     373, uint(QxtSpanSlider::NoOverlapping),

       0        // eod
};

static const char qt_meta_stringdata_QxtSpanSlider[] = {
    "QxtSpanSlider\0\0lower,upper\0"
    "spanChanged(int,int)\0lower\0"
    "lowerValueChanged(int)\0upper\0"
    "upperValueChanged(int)\0lowerPositionChanged(int)\0"
    "upperPositionChanged(int)\0setLowerValue(int)\0"
    "setUpperValue(int)\0setSpan(int,int)\0"
    "setLowerPosition(int)\0setUpperPosition(int)\0"
    "int\0lowerValue\0upperValue\0lowerPosition\0"
    "upperPosition\0HandleMovementMode\0"
    "handleMovementMode\0FreeMovement\0"
    "NoCrossing\0NoOverlapping\0"
};

const QMetaObject QxtSpanSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_QxtSpanSlider,
      qt_meta_data_QxtSpanSlider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSpanSlider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSpanSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSpanSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSpanSlider))
        return static_cast<void*>(const_cast< QxtSpanSlider*>(this));
    return QSlider::qt_metacast(_clname);
}

int QxtSpanSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: spanChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: lowerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: upperValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: lowerPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: upperPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setLowerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setUpperValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setSpan((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: setLowerPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setUpperPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = lowerValue(); break;
        case 1: *reinterpret_cast< int*>(_v) = upperValue(); break;
        case 2: *reinterpret_cast< int*>(_v) = lowerPosition(); break;
        case 3: *reinterpret_cast< int*>(_v) = upperPosition(); break;
        case 4: *reinterpret_cast< HandleMovementMode*>(_v) = handleMovementMode(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setLowerValue(*reinterpret_cast< int*>(_v)); break;
        case 1: setUpperValue(*reinterpret_cast< int*>(_v)); break;
        case 2: setLowerPosition(*reinterpret_cast< int*>(_v)); break;
        case 3: setUpperPosition(*reinterpret_cast< int*>(_v)); break;
        case 4: setHandleMovementMode(*reinterpret_cast< HandleMovementMode*>(_v)); break;
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

// SIGNAL 0
void QxtSpanSlider::spanChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtSpanSlider::lowerValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtSpanSlider::upperValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QxtSpanSlider::lowerPositionChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QxtSpanSlider::upperPositionChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
