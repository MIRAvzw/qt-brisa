/****************************************************************************
** Meta object code from reading C++ file 'qxtnamespace.h'
**
** Created: Mon May 3 17:54:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtnamespace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtnamespace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Qxt[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       4, 0x0,    4,   26,
      13, 0x0,    3,   34,
      29, 0x0,   22,   40,

 // enum data: key, value
      39, uint(Qxt::NoRotation),
      50, uint(Qxt::UpsideDown),
      61, uint(Qxt::Clockwise),
      71, uint(Qxt::CounterClockwise),
      88, uint(Qxt::NoDecoration),
     101, uint(Qxt::Buttonlike),
     112, uint(Qxt::Menulike),
     121, uint(Qxt::NoError),
     129, uint(Qxt::UnknownError),
     142, uint(Qxt::LogicalError),
     155, uint(Qxt::Bug),
     159, uint(Qxt::UnexpectedEndOfFunction),
     183, uint(Qxt::NotImplemented),
     198, uint(Qxt::CodecError),
     209, uint(Qxt::NotInitialised),
     224, uint(Qxt::EndOfFile),
     234, uint(Qxt::FileIOError),
     246, uint(Qxt::FormatError),
     258, uint(Qxt::DeviceError),
     270, uint(Qxt::SDLError),
     279, uint(Qxt::InsufficientMemory),
     298, uint(Qxt::SeeErrorString),
     313, uint(Qxt::UnexpectedNullParameter),
     337, uint(Qxt::ClientTimeout),
     351, uint(Qxt::SocketIOError),
     365, uint(Qxt::ParserError),
     377, uint(Qxt::HeaderTooLong),
     391, uint(Qxt::Auth),
     396, uint(Qxt::Overflow),

       0        // eod
};

static const char qt_meta_stringdata_Qxt[] = {
    "Qxt\0Rotation\0DecorationStyle\0ErrorCode\0"
    "NoRotation\0UpsideDown\0Clockwise\0"
    "CounterClockwise\0NoDecoration\0Buttonlike\0"
    "Menulike\0NoError\0UnknownError\0"
    "LogicalError\0Bug\0UnexpectedEndOfFunction\0"
    "NotImplemented\0CodecError\0NotInitialised\0"
    "EndOfFile\0FileIOError\0FormatError\0"
    "DeviceError\0SDLError\0InsufficientMemory\0"
    "SeeErrorString\0UnexpectedNullParameter\0"
    "ClientTimeout\0SocketIOError\0ParserError\0"
    "HeaderTooLong\0Auth\0Overflow\0"
};

const QMetaObject Qxt::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Qxt,
      qt_meta_data_Qxt, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Qxt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Qxt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Qxt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qxt))
        return static_cast<void*>(const_cast< Qxt*>(this));
    return QObject::qt_metacast(_clname);
}

int Qxt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
