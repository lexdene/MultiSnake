/****************************************************************************
** Meta object code from reading C++ file 'jsocketbase.h'
**
** Created: Fri Aug 19 08:59:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/network/jsocketbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsocketbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JSocketBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      36,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   12,   12,   12, 0x09,
      79,   12,   12,   12, 0x09,
     104,   12,   12,   12, 0x09,
     138,  126,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_JSocketBase[] = {
    "JSocketBase\0\0code\0SocketCode(JCode)\0"
    "SocketError(QString)\0on_socket_connected()\0"
    "on_socket_disconnected()\0on_socket_readyRead()\0"
    "socketError\0on_socket_error(QAbstractSocket::SocketError)\0"
};

const QMetaObject JSocketBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JSocketBase,
      qt_meta_data_JSocketBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JSocketBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JSocketBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JSocketBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JSocketBase))
        return static_cast<void*>(const_cast< JSocketBase*>(this));
    return QObject::qt_metacast(_clname);
}

int JSocketBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SocketCode((*reinterpret_cast< JCode(*)>(_a[1]))); break;
        case 1: SocketError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: on_socket_connected(); break;
        case 3: on_socket_disconnected(); break;
        case 4: on_socket_readyRead(); break;
        case 5: on_socket_error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void JSocketBase::SocketCode(JCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JSocketBase::SocketError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
