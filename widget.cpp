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
	
	btnAddEmployee = new QPushButton(QString::fromLocal8Bit("&�������� ����������"));
	btnDelEmployee = new QPushButton(QString::fromLocal8Bit("&������� ����������"));
	btnChangePosition = new QPushButton(QString::fromLocal8Bit("&�������� ��� ����������"));
	btnAssociateEmployee = new QPushButton(QString::fromLocal8Bit("&����������� ���������� � ���������"));
	btnSortLastname = new QPushButton(QString::fromLocal8Bit("&����������� ������ �� ��������"));
	btnSortDate = new QPushButton(QString::fromLocal8Bit("&����������� ����� �������� �� ������"));
	btnPrintEmployeeList = new QPushButton(QString::fromLocal8Bit("&������� ������ ����������"));
	btnGetListAssociate = new QPushButton(QString::fromLocal8Bit("&������� ������ ���������� ���������� � ���������"));
	btnExit = new QPushButton(QString::fromLocal8Bit("&�����"));

	QObject::connect(btnAssociateEmployee, &QPushButton::clicked, this, &Widget::PrintEmployeeList);



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

void Widget::PrintEmployeeList()
{
	{
		QStringList lst;
		lst << QString::fromLocal8Bit("���") << QString::fromLocal8Bit("�������");

		tbl->setHorizontalHeaderLabels(lst);
	}

	std::vector< Employee2* > emplyeesVec = company2.GetEmployees();

	tbl->setColumnCount(2);
	tbl->setRowCount(emplyeesVec.size());

	QTableWidgetItem* ptwi = nullptr;

	for (int i = 0; i < emplyeesVec.size(); ++i) {

		ptwi = new QTableWidgetItem(QString::fromStdString( emplyeesVec[i]->GetFirstName() ) );
		tbl->setItem(i, 0, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetLastName()));
		tbl->setItem(i, 1, ptwi);
	}
}
