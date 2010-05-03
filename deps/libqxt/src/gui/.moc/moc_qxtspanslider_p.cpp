/****************************************************************************
** Meta object code from reading C++ file 'qxtspanslider_p.h'
**
** Created: Mon May 3 17:55:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtspanslider_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtspanslider_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtSpanSliderPrivate[] = {

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
      30,   22,   21,   21, 0x0a,
      51,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtSpanSliderPrivate[] = {
    "QxtSpanSliderPrivate\0\0min,max\0"
    "updateRange(int,int)\0movePressedHandle()\0"
};

const QMetaObject QxtSpanSliderPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtSpanSliderPrivate,
      qt_meta_data_QxtSpanSliderPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtSpanSliderPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtSpanSliderPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtSpanSliderPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSpanSliderPrivate))
        return static_cast<void*>(const_cast< QxtSpanSliderPrivate*>(this));
    if (!strcmp(_clname, "QxtPrivate<QxtSpanSlider>"))
        return static_cast< QxtPrivate<QxtSpanSlider>*>(const_cast< QxtSpanSliderPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtSpanSliderPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: movePressedHandle(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
