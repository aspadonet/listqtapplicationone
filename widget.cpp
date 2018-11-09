#include "widget.h"
#include <QtWidgets>
#include "stdafx.h"

#include "Employee.h"
#include "File.h"
#include "Position.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
Widget::Widget(QWidget *parent)
	: QWidget(parent)


{	
	
	btnAddEmployee = new QPushButton(QString::fromLocal8Bit("&добавить сотрудника"));
	btnDelEmployee = new QPushButton(QString::fromLocal8Bit("&удалить сотрудника"));
	btnChangePosition = new QPushButton(QString::fromLocal8Bit("&изменить тип сотрудника"));
	btnAssociateEmployee = new QPushButton(QString::fromLocal8Bit("&привязывать сотрудника к менеджеру"));
	btnSortLastname = new QPushButton(QString::fromLocal8Bit("&сортировать список по фамилиям"));
	btnSortDate = new QPushButton(QString::fromLocal8Bit("&сортировать датам принятия на работу"));
	btnPrintEmployeeList = new QPushButton(QString::fromLocal8Bit("&вывести список работников"));
	btnGetListAssociate = new QPushButton(QString::fromLocal8Bit("&вывести список работников привязаных к менеджеру"));
	btnExit = new QPushButton(QString::fromLocal8Bit("&Выход"));

	QObject::connect(btnAssociateEmployee, &QPushButton::clicked, this, &Widget::PrintEmployeeList);
	QObject::connect(btnAddEmployee, &QPushButton::clicked, this, &Widget::AddEmployee);


	//lst << "First" << "Second" << "Third" << "Second" << "Third";
	tbl = new QTableWidget(n,n);
/*       tbl->setHorizontalHeaderLabels(lst);
	   tbl->setVerticalHeaderLabels(lst);

	   for (int i  = 0; i < 5; ++i) {
		   for (int j = 0; j < 5; ++j) {
			   ptwi = new QTableWidgetItem(QString("%1,%2").arg(i).arg(j));
			   tbl->setItem(i, j, ptwi);
		   }
	   }
	   */
	tbl->resize(400, 400);



	//Layout setup
	pvbxLayout = new QVBoxLayout;
	pvbxLayout->addWidget(tbl);
	pvbxLayout->addWidget(btnAddEmployee);
	pvbxLayout->addWidget(btnDelEmployee);
	pvbxLayout->addWidget(btnChangePosition);
	pvbxLayout->addWidget(btnAssociateEmployee);
	pvbxLayout->addWidget(btnSortLastname);
	pvbxLayout->addWidget(btnSortDate);
	pvbxLayout->addWidget(btnPrintEmployeeList);
	pvbxLayout->addWidget(btnGetListAssociate);
	pvbxLayout->addWidget(btnExit);
	setLayout(pvbxLayout);

	File2 ftemp;

	ftemp.ReadEmplyeesList(company2);
	PrintEmployeeList();
}

Widget::~Widget()
{

}

void Widget::AddEmployee()
{
	QWidget widgetAddEmployee;

	widgetAddEmployee.resize(100,100);
	widgetAddEmployee.show();



}
void Widget::DelEmployee()
{}
void Widget::ChangePosition()
{}
void Widget::AssociateEmployee()
{}
void Widget::SortLastname()
{}
void Widget::SortDate()
{}
void Widget::GetListAssociate()
{}
void Widget::PrintEmployeeList()
{
	{
		QStringList lst;
		lst << QString::fromLocal8Bit("Должность")
			<< QString::fromLocal8Bit("Фамилия")
			<< QString::fromLocal8Bit("Имя")
			<< QString::fromLocal8Bit("Отчество")
			<< QString::fromLocal8Bit("Дата рождения")
			<< QString::fromLocal8Bit("Дата устройство на работу");

		tbl->setHorizontalHeaderLabels(lst);
	}

	std::vector< Employee2* > emplyeesVec = company2.GetEmployees();

	tbl->setColumnCount(6);
	tbl->setRowCount(emplyeesVec.size());

	QTableWidgetItem* ptwi = nullptr;

	for (int i = 0; i < emplyeesVec.size(); ++i) {

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetPositionName()));
		tbl->setItem(i, 0, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetLastName()));
		tbl->setItem(i, 1, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetFirstName()));
		tbl->setItem(i, 2, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetPatronymic()));
		tbl->setItem(i, 3, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString( emplyeesVec[i]->GetDateOfBirth() ) );
		tbl->setItem(i, 4, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetDateOfHiring()));
		tbl->setItem(i, 5, ptwi);
	}

	
	
}
