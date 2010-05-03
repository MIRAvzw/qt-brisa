/****************************************************************************
** Meta object code from reading C++ file 'qxtflowview_p.h'
**
** Created: Mon May 3 17:55:03 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtflowview_p.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtflowview_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtFlowViewPrivate[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   20,   19,   19, 0x0a,
      83,   20,   19,   19, 0x0a,
     128,   20,   19,   19, 0x0a,
     165,   20,   19,   19, 0x0a,
     221,  201,   19,   19, 0x0a,
     281,  258,   19,   19, 0x0a,
     324,   19,   19,   19, 0x0a,
     349,   19,   19,   19, 0x0a,
     365,   19,   19,   19, 0x0a,
     387,   19,   19,   19, 0x0a,
     400,   20,   19,   19, 0x0a,
     443,   20,   19,   19, 0x0a,
     485,   20,   19,   19, 0x0a,
     519,   20,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QxtFlowViewPrivate[] = {
    "QxtFlowViewPrivate\0\0parent,start,end\0"
    "columnsAboutToBeInserted(QModelIndex,int,int)\0"
    "columnsAboutToBeRemoved(QModelIndex,int,int)\0"
    "columnsInserted(QModelIndex,int,int)\0"
    "columnsRemoved(QModelIndex,int,int)\0"
    "topLeft,bottomRight\0"
    "dataChanged(QModelIndex,QModelIndex)\0"
    "orientation,first,last\0"
    "headerDataChanged(Qt::Orientation,int,int)\0"
    "layoutAboutToBeChanged()\0layoutChanged()\0"
    "modelAboutToBeReset()\0modelReset()\0"
    "rowsAboutToBeInserted(QModelIndex,int,int)\0"
    "rowsAboutToBeRemoved(QModelIndex,int,int)\0"
    "rowsInserted(QModelIndex,int,int)\0"
    "rowsRemoved(QModelIndex,int,int)\0"
};

const QMetaObject QxtFlowViewPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtFlowViewPrivate,
      qt_meta_data_QxtFlowViewPrivate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtFlowViewPrivate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtFlowViewPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtFlowViewPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtFlowViewPrivate))
        return static_cast<void*>(const_cast< QxtFlowViewPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtFlowViewPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: columnsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: columnsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: columnsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: columnsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 5: headerDataChanged((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: layoutAboutToBeChanged(); break;
        case 7: layoutChanged(); break;
        case 8: modelAboutToBeReset(); break;
        case 9: modelReset(); break;
        case 10: rowsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: rowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
