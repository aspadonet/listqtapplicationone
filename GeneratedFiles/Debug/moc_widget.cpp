/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[32];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 17), // "PrintEmployeeList"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "AddEmployee"
QT_MOC_LITERAL(4, 38, 12), // "EditEmployee"
QT_MOC_LITERAL(5, 51, 3), // "row"
QT_MOC_LITERAL(6, 55, 14), // "EditEmployeeCM"
QT_MOC_LITERAL(7, 70, 11), // "DelEmployee"
QT_MOC_LITERAL(8, 82, 13), // "DelEmployeeCM"
QT_MOC_LITERAL(9, 96, 14), // "ChangePosition"
QT_MOC_LITERAL(10, 111, 17), // "AssociateEmployee"
QT_MOC_LITERAL(11, 129, 12), // "SortLastname"
QT_MOC_LITERAL(12, 142, 8), // "SortDate"
QT_MOC_LITERAL(13, 151, 16), // "GetListAssociate"
QT_MOC_LITERAL(14, 168, 18), // "GetListAssociateCM"
QT_MOC_LITERAL(15, 187, 8), // "ExitList"
QT_MOC_LITERAL(16, 196, 23), // "slotCustomMenuRequested"
QT_MOC_LITERAL(17, 220, 3), // "pos"
QT_MOC_LITERAL(18, 224, 15), // "getOpenFileName"
QT_MOC_LITERAL(19, 240, 15), // "getSaveFileName"
QT_MOC_LITERAL(20, 256, 8), // "SaveFile"
QT_MOC_LITERAL(21, 265, 11), // "SaveXMLFile"
QT_MOC_LITERAL(22, 277, 11), // "ReadXMLFile"
QT_MOC_LITERAL(23, 289, 11), // "SaveSqlFile"
QT_MOC_LITERAL(24, 301, 11), // "ReadSqlFile"
QT_MOC_LITERAL(25, 313, 12), // "tempFromFile"
QT_MOC_LITERAL(26, 326, 8), // "lastName"
QT_MOC_LITERAL(27, 335, 11), // "std::string"
QT_MOC_LITERAL(28, 347, 9), // "firstName"
QT_MOC_LITERAL(29, 357, 10), // "patronymic"
QT_MOC_LITERAL(30, 368, 11), // "dateOfBirth"
QT_MOC_LITERAL(31, 380, 12) // "dateOfHiring"

    },
    "Widget\0PrintEmployeeList\0\0AddEmployee\0"
    "EditEmployee\0row\0EditEmployeeCM\0"
    "DelEmployee\0DelEmployeeCM\0ChangePosition\0"
    "AssociateEmployee\0SortLastname\0SortDate\0"
    "GetListAssociate\0GetListAssociateCM\0"
    "ExitList\0slotCustomMenuRequested\0pos\0"
    "getOpenFileName\0getSaveFileName\0"
    "SaveFile\0SaveXMLFile\0ReadXMLFile\0"
    "SaveSqlFile\0ReadSqlFile\0tempFromFile\0"
    "lastName\0std::string\0firstName\0"
    "patronymic\0dateOfBirth\0dateOfHiring"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x08 /* Private */,
       3,    0,  125,    2, 0x08 /* Private */,
       4,    1,  126,    2, 0x08 /* Private */,
       6,    0,  129,    2, 0x08 /* Private */,
       7,    0,  130,    2, 0x08 /* Private */,
       8,    0,  131,    2, 0x08 /* Private */,
       9,    0,  132,    2, 0x08 /* Private */,
      10,    0,  133,    2, 0x08 /* Private */,
      11,    0,  134,    2, 0x08 /* Private */,
      12,    0,  135,    2, 0x08 /* Private */,
      13,    0,  136,    2, 0x08 /* Private */,
      14,    0,  137,    2, 0x08 /* Private */,
      15,    0,  138,    2, 0x08 /* Private */,
      16,    1,  139,    2, 0x08 /* Private */,
      18,    0,  142,    2, 0x08 /* Private */,
      19,    0,  143,    2, 0x08 /* Private */,
      20,    0,  144,    2, 0x08 /* Private */,
      21,    0,  145,    2, 0x08 /* Private */,
      22,    0,  146,    2, 0x08 /* Private */,
      23,    0,  147,    2, 0x08 /* Private */,
      24,    0,  148,    2, 0x08 /* Private */,
      25,    6,  149,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
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
    QMetaType::Void, QMetaType::QPoint,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 27, QMetaType::QString, QMetaType::QString, QMetaType::QDate, QMetaType::QDate,   26,   17,   28,   29,   30,   31,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PrintEmployeeList(); break;
        case 1: _t->AddEmployee(); break;
        case 2: _t->EditEmployee((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->EditEmployeeCM(); break;
        case 4: _t->DelEmployee(); break;
        case 5: _t->DelEmployeeCM(); break;
        case 6: _t->ChangePosition(); break;
        case 7: _t->AssociateEmployee(); break;
        case 8: _t->SortLastname(); break;
        case 9: _t->SortDate(); break;
        case 10: _t->GetListAssociate(); break;
        case 11: _t->GetListAssociateCM(); break;
        case 12: _t->ExitList(); break;
        case 13: _t->slotCustomMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 14: _t->getOpenFileName(); break;
        case 15: _t->getSaveFileName(); break;
        case 16: _t->SaveFile(); break;
        case 17: _t->SaveXMLFile(); break;
        case 18: _t->ReadXMLFile(); break;
        case 19: _t->SaveSqlFile(); break;
        case 20: _t->ReadSqlFile(); break;
        case 21: _t->tempFromFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< const QDate(*)>(_a[5])),(*reinterpret_cast< const QDate(*)>(_a[6]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
