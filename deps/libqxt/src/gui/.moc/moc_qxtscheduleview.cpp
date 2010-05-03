/****************************************************************************
** Meta object code from reading C++ file 'qxtscheduleview.h'
**
** Created: Mon May 3 17:55:21 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtscheduleview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtscheduleview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtScheduleView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   17,   16,   16, 0x05,
      70,   64,   16,   16, 0x05,
      97,   64,   16,   16, 0x05,
     129,   64,   16,   16, 0x05,
     181,  163,   16,   16, 0x05,
     211,  199,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     252,  232,   16,   16, 0x0a,
     289,   16,   16,   16, 0x0a,
     308,   16,   16,   16, 0x0a,
     317,   16,   16,   16, 0x0a,
     344,  327,   16,   16, 0x09,
     386,  327,   16,   16, 0x09,
     429,  327,   16,   16, 0x09,
     462,  327,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QxtScheduleView[] = {
    "QxtScheduleView\0\0rows,cols,index\0"
    "itemMoved(int,int,QModelIndex)\0index\0"
    "indexSelected(QModelIndex)\0"
    "indexDoubleClicked(QModelIndex)\0"
    "contextMenuRequested(QModelIndex)\0"
    "newDepthInSeconds\0newZoomDepth(int)\0"
    "newViewMode\0viewModeChanged(int)\0"
    "topLeft,bottomRight\0"
    "dataChanged(QModelIndex,QModelIndex)\0"
    "updateGeometries()\0zoomIn()\0zoomOut()\0"
    "parent,start,end\0"
    "rowsAboutToBeRemoved(QModelIndex,int,int)\0"
    "rowsAboutToBeInserted(QModelIndex,int,int)\0"
    "rowsRemoved(QModelIndex,int,int)\0"
    "rowsInserted(QModelIndex,int,int)\0"
};

const QMetaObject QxtScheduleView::staticMetaObject = {
    { &QAbstractScrollArea::staticMetaObject, qt_meta_stringdata_QxtScheduleView,
      qt_meta_data_QxtScheduleView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtScheduleView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtScheduleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtScheduleView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtScheduleView))
        return static_cast<void*>(const_cast< QxtScheduleView*>(this));
    return QAbstractScrollArea::qt_metacast(_clname);
}

int QxtScheduleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QModelIndex(*)>(_a[3]))); break;
        case 1: indexSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: indexDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: contextMenuRequested((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: newZoomDepth((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: viewModeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 7: updateGeometries(); break;
        case 8: zoomIn(); break;
        case 9: zoomOut(); break;
        case 10: rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: rowsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: rowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QxtScheduleView::itemMoved(int _t1, int _t2, QModelIndex _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtScheduleView::indexSelected(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtScheduleView::indexDoubleClicked(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QxtScheduleView::contextMenuRequested(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QxtScheduleView::newZoomDepth(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QxtScheduleView::viewModeChanged(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
