/****************************************************************************
** Meta object code from reading C++ file 'IFSImageLabel.h'
**
** Created: Sun May 4 16:38:39 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "IFSImageLabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IFSImageLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IFSImageLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   15,   14,   14, 0x05,
      60,   51,   14,   14, 0x05,
      92,   80,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,   14,   14,   14, 0x0a,
     134,   14,   14,   14, 0x0a,
     155,   14,   14,   14, 0x0a,
     182,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IFSImageLabel[] = {
    "IFSImageLabel\0\0inputValue\0"
    "imageCursorValue(double)\0inputRow\0"
    "imageCursorRow(int)\0inputColumn\0"
    "imageCursorColumn(int)\0setPixmap(QPixmap)\0"
    "setIFSImage(IFSHDR*)\0resizeEvent(QResizeEvent*)\0"
    "mouseMoveEvent(QMouseEvent*)\0"
};

void IFSImageLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IFSImageLabel *_t = static_cast<IFSImageLabel *>(_o);
        switch (_id) {
        case 0: _t->imageCursorValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->imageCursorRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->imageCursorColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 4: _t->setIFSImage((*reinterpret_cast< IFSHDR*(*)>(_a[1]))); break;
        case 5: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IFSImageLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IFSImageLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_IFSImageLabel,
      qt_meta_data_IFSImageLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IFSImageLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IFSImageLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IFSImageLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IFSImageLabel))
        return static_cast<void*>(const_cast< IFSImageLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int IFSImageLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void IFSImageLabel::imageCursorValue(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IFSImageLabel::imageCursorRow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IFSImageLabel::imageCursorColumn(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
