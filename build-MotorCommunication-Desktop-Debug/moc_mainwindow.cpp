/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MotorCommunication/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_btnConnected_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "on_btnServo_clicked"
QT_MOC_LITERAL(4, 56, 10), // "Thread_Pos"
QT_MOC_LITERAL(5, 67, 4), // "Read"
QT_MOC_LITERAL(6, 72, 18), // "on_btnHome_clicked"
QT_MOC_LITERAL(7, 91, 19), // "on_btnMoveJ_clicked"
QT_MOC_LITERAL(8, 111, 26), // "on_chkCartesianPos_clicked"
QT_MOC_LITERAL(9, 138, 22), // "on_btnTeaching_clicked"
QT_MOC_LITERAL(10, 161, 23), // "on_chkcarPulPos_clicked"
QT_MOC_LITERAL(11, 185, 23), // "on_btnClearData_clicked"
QT_MOC_LITERAL(12, 209, 20), // "on_btnImport_clicked"
QT_MOC_LITERAL(13, 230, 20), // "on_btnDelete_clicked"
QT_MOC_LITERAL(14, 251, 22), // "on_btnPlayback_clicked"
QT_MOC_LITERAL(15, 274, 21), // "on_btnLoadJob_clicked"
QT_MOC_LITERAL(16, 296, 22) // "on_btnStartJob_clicked"

    },
    "MainWindow\0on_btnConnected_clicked\0\0"
    "on_btnServo_clicked\0Thread_Pos\0Read\0"
    "on_btnHome_clicked\0on_btnMoveJ_clicked\0"
    "on_chkCartesianPos_clicked\0"
    "on_btnTeaching_clicked\0on_chkcarPulPos_clicked\0"
    "on_btnClearData_clicked\0on_btnImport_clicked\0"
    "on_btnDelete_clicked\0on_btnPlayback_clicked\0"
    "on_btnLoadJob_clicked\0on_btnStartJob_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnConnected_clicked(); break;
        case 1: _t->on_btnServo_clicked(); break;
        case 2: _t->Thread_Pos(); break;
        case 3: _t->Read(); break;
        case 4: _t->on_btnHome_clicked(); break;
        case 5: _t->on_btnMoveJ_clicked(); break;
        case 6: _t->on_chkCartesianPos_clicked(); break;
        case 7: _t->on_btnTeaching_clicked(); break;
        case 8: _t->on_chkcarPulPos_clicked(); break;
        case 9: _t->on_btnClearData_clicked(); break;
        case 10: _t->on_btnImport_clicked(); break;
        case 11: _t->on_btnDelete_clicked(); break;
        case 12: _t->on_btnPlayback_clicked(); break;
        case 13: _t->on_btnLoadJob_clicked(); break;
        case 14: _t->on_btnStartJob_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
