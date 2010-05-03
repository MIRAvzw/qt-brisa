/****************************************************************************
** Meta object code from reading C++ file 'qxtlanguagecombobox.h'
**
** Created: Mon May 3 17:55:10 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qxtlanguagecombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtlanguagecombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QxtLanguageComboBox[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       4,   39, // properties
       1,   51, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   21,   20,   20, 0x05,
      76,   71,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     117,  112,   20,   20, 0x0a,
     160,  155,   20,   20, 0x0a,
     193,  188,   20,   20, 0x0a,

 // properties: name, type, flags
     229,  221, 0x0a095001,
     267,  249, 0x0009510b,
     295,  283, 0x0009510b,
     307,  221, 0x0a095103,

 // enums: name, flags, count, data
     283, 0x0,    2,   55,

 // enum data: key, value
     323, uint(QxtLanguageComboBox::AllLanguages),
     336, uint(QxtLanguageComboBox::AvailableTranslations),

       0        // eod
};

static const char qt_meta_stringdata_QxtLanguageComboBox[] = {
    "QxtLanguageComboBox\0\0country\0"
    "currentLanguageChanged(QLocale::Language)\0"
    "name\0currentLanguageNameChanged(QString)\0"
    "lang\0setCurrentLanguage(QLocale::Language)\0"
    "mode\0setDisplayMode(DisplayMode)\0path\0"
    "setTranslationPath(QString)\0QString\0"
    "currentLanguageName\0QLocale::Language\0"
    "currentLanguage\0DisplayMode\0displayMode\0"
    "translationPath\0AllLanguages\0"
    "AvailableTranslations\0"
};

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QxtLanguageComboBox[] = {
        QLocale::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QxtLanguageComboBox[] = {
        &QLocale::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

static const QMetaObjectExtraData qt_meta_extradata2_QxtLanguageComboBox = {
    qt_meta_extradata_QxtLanguageComboBox, 0 
};

const QMetaObject QxtLanguageComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_QxtLanguageComboBox,
      qt_meta_data_QxtLanguageComboBox, &qt_meta_extradata2_QxtLanguageComboBox }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QxtLanguageComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QxtLanguageComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QxtLanguageComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QxtLanguageComboBox))
        return static_cast<void*>(const_cast< QxtLanguageComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int QxtLanguageComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentLanguageChanged((*reinterpret_cast< QLocale::Language(*)>(_a[1]))); break;
        case 1: currentLanguageNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: setCurrentLanguage((*reinterpret_cast< QLocale::Language(*)>(_a[1]))); break;
        case 3: setDisplayMode((*reinterpret_cast< DisplayMode(*)>(_a[1]))); break;
        case 4: setTranslationPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = currentLanguageName(); break;
        case 1: *reinterpret_cast< QLocale::Language*>(_v) = currentLanguage(); break;
        case 2: *reinterpret_cast< DisplayMode*>(_v) = displayMode(); break;
        case 3: *reinterpret_cast< QString*>(_v) = translationPath(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setCurrentLanguage(*reinterpret_cast< QLocale::Language*>(_v)); break;
        case 2: setDisplayMode(*reinterpret_cast< DisplayMode*>(_v)); break;
        case 3: setTranslationPath(*reinterpret_cast< QString*>(_v)); break;
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
void QxtLanguageComboBox::currentLanguageChanged(QLocale::Language _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QxtLanguageComboBox::currentLanguageNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
