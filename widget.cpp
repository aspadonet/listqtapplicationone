#include "widget.h"
#include <QtWidgets>
#include "stdafx.h"

#include "Employee.h"
#include "File.h"
#include "Company.h"
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
	Company2 company2;
	
	File2 ftemp;

	ftemp.ReadEmplyeesList(company2);

	ADD_EMPLOYEE = new QPushButton(QString::fromLocal8Bit("&ADD_EMPLOYEE добавить сотрудника"));
	DEL_EMPLOYEE = new QPushButton(QString::fromLocal8Bit("&DEL_EMPLOYEE удалить сотрудника"));
	CHANGE_POSITION = new QPushButton(QString::fromLocal8Bit("&CHANGE_POSITION изменить тип сотрудника"));
	ASSOCIATE_EMPLOYEE = new QPushButton(QString::fromLocal8Bit("&привязывать сотрудника к менеджеру"));
	SORT_LASTNAME = new QPushButton(QString::fromLocal8Bit("&сортировать список по фамилиям"));
	SORT_DATE = new QPushButton(QString::fromLocal8Bit("&сортировать датам принятия на работу"));
	PRINT_EMPLYEES_LIST = new QPushButton(QString::fromLocal8Bit("&PRINT_EMPLYEES_LISTвывести список работников"));
	GET_LIST_ASSOCIATE = new QPushButton(QString::fromLocal8Bit("&вывести список работников привязаных к менеджеру"));
	EXIT = new QPushButton(QString::fromLocal8Bit("&Выход"));
	QObject::connect(PRINT_EMPLYEES_LIST, &QPushButton::clicked, this, &Widget::PRINT_EMPLYEES_LISTBtnClicked);



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
	pvbxLayout->addWidget(ADD_EMPLOYEE);
	pvbxLayout->addWidget(DEL_EMPLOYEE);
	pvbxLayout->addWidget(CHANGE_POSITION);
	pvbxLayout->addWidget(ASSOCIATE_EMPLOYEE);
	pvbxLayout->addWidget(SORT_LASTNAME);
	pvbxLayout->addWidget(SORT_DATE);
	pvbxLayout->addWidget(PRINT_EMPLYEES_LIST);
	pvbxLayout->addWidget(GET_LIST_ASSOCIATE);
	pvbxLayout->addWidget(EXIT);
	setLayout(pvbxLayout);
}

Widget::~Widget()
{

}

void Widget::PRINT_EMPLYEES_LISTBtnClicked()
{
	lst << "Должность"<< "Фамилия"<< "Имя"<< "Отчество"<< "Дата"<<"Дата";
	tbl->setHorizontalHeaderLabels(lst);
	//tbl->setVerticalHeaderLabels(lst);

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			ptwi = new QTableWidgetItem(QString("%1,%2").arg(i).arg(j));
			tbl->setItem(i, j, ptwi);
		}
	}

	/*for (Employee2* emp2 : company.GetEmployees())
	{
		PrintReportRow(emp2->GetPositionName(), emp2->GetLastName(), emp2->GetFirstName(), emp2->GetPatronymic(), emp2->GetDateOfBirth(), emp2->GetDateOfHiring());
	}*/
}
