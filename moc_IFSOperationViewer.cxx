/****************************************************************************
** Meta object code from reading C++ file 'IFSOperationViewer.h'
**
** Created: Sun May 4 15:45:08 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "IFSOperationViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IFSOperationViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IFSOperationViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      31,   19,   19,   19, 0x0a,
      42,   19,   19,   19, 0x0a,
      49,   19,   19,   19, 0x0a,
      63,   19,   19,   19, 0x0a,
      94,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IFSOperationViewer[] = {
    "IFSOperationViewer\0\0openFile()\0"
    "saveFile()\0swap()\0setFrame(int)\0"
    "setupParameterWidgets(QString)\0"
    "applyOperation()\0"
};

void IFSOperationViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IFSOperationViewer *_t = static_cast<IFSOperationViewer *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->swap(); break;
        case 3: _t->setFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setupParameterWidgets((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->applyOperation(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IFSOperationViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IFSOperationViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IFSOperationViewer,
      qt_meta_data_IFSOperationViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IFSOperationViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IFSOperationViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IFSOperationViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IFSOperationViewer))
        return static_cast<void*>(const_cast< IFSOperationViewer*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< IFSOperationViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IFSOperationViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
