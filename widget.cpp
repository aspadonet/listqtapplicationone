#include "stdafx.h"

#include "widget.h"
#include <QtWidgets>

#include "utils.h"

#include "Employee.h"
#include "File.h"
#include "Position.h"

#include "EmployeeDialog.h"
#include "DeleteEmployeeDialog.h"
#include "ChangePositionDialog.h"
#include "AssociateAnEmployeeWithAManagerDialog.h"
#include "GetListAssociateAnEmployeeWithAManagerDialog.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
Widget::Widget(QWidget *parent)
	: QWidget(parent)


{	
	
	btnAddEmployee = new QPushButton(QString::fromLocal8Bit("&добавить сотрудника НЕТ ВАЛИДАЦИИ!!!"));
	btnDelEmployee = new QPushButton(QString::fromLocal8Bit("&удалить сотрудника"));
	btnChangePosition = new QPushButton(QString::fromLocal8Bit("&изменить тип сотрудника"));
	btnAssociateEmployee = new QPushButton(QString::fromLocal8Bit("&привязывать сотрудника к менеджеру"));
	btnSortLastname = new QPushButton(QString::fromLocal8Bit("&сортировать список по фамилиям"));
	btnSortDate = new QPushButton(QString::fromLocal8Bit("&сортировать датам принятия на работу"));
	btnPrintEmployeeList = new QPushButton(QString::fromLocal8Bit("&вывести список работников"));
	btnGetListAssociate = new QPushButton(QString::fromLocal8Bit("&вывести список работников привязаных к менеджеру"));
	btnExit = new QPushButton(QString::fromLocal8Bit("&Сохранить изменения и завершить работу"));

	//QObject::connect(btnExit, &QPushButton::clicked, &a, &a::quit());
	QObject::connect(btnDelEmployee, &QPushButton::clicked, this, &Widget::DelEmployee);
	QObject::connect(btnAddEmployee, &QPushButton::clicked, this, &Widget::AddEmployee);
	QObject::connect(btnChangePosition, &QPushButton::clicked, this, &Widget::ChangePosition);
	QObject::connect(btnAssociateEmployee, &QPushButton::clicked, this, &Widget::AssociateEmployee);
	QObject::connect(btnSortLastname, &QPushButton::clicked, this, &Widget::SortLastname);
	QObject::connect(btnSortDate, &QPushButton::clicked, this, &Widget::SortDate);
	QObject::connect(btnPrintEmployeeList, &QPushButton::clicked, this, &Widget::PrintEmployeeList);
	QObject::connect(btnGetListAssociate, &QPushButton::clicked, this, &Widget::GetListAssociate);
	QObject::connect(btnExit, &QPushButton::clicked, this, &Widget::ExitList);
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
		
	ftemp.ReadEmplyeesList(company2);
	
	PrintEmployeeList();
}

Widget::~Widget()
{

}

void Widget::AddEmployee()
{
	EmployeeDialog widgetAddEmployee;

	widgetAddEmployee.resize(100,100);

	//int res = widgetAddEmployee.exec();
	//long sdf = 789;

	if (QDialog::Rejected == widgetAddEmployee.exec())
		return;

	Employee2* emp = widgetAddEmployee.getEmploee();
	
	company2.AddEmployee( emp );

//	widgetAddEmployee.leName.getText();
//	Employee2 emp = widgetAddEmployee.getEmploee();
	
	PrintEmployeeList();
}

void Widget::DelEmployee()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	DeleteEmployeeDialog widgetDeleteEmployee(employees);
	
	widgetDeleteEmployee.resize(100,100);
	
	if (QDialog::Rejected == widgetDeleteEmployee.exec())
		return;

	std::string lastName = widgetDeleteEmployee.getLastName();
	
	company2.DeleteEmployee2(lastName);

	//widgetDeleteEmployeeDialog.show();
}
void Widget::ChangePosition()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	ChangePositionDialog widgetChangePositionDialog(employees);
	
	widgetChangePositionDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetChangePositionDialog.exec())
		return;

	std::string lastName = widgetChangePositionDialog.getLastName();
	
	Position* pos = nullptr;
	
	pos = widgetChangePositionDialog.getPositionName();
	
	company2.ChangePosition(lastName, pos);
	

}
void Widget::AssociateEmployee()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	AssociateAnEmployeeWithAManagerDialog widgetAssociateAnEmployeeWithAManagerDialog(employees);
	
	widgetAssociateAnEmployeeWithAManagerDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	std::string lastNameManager = widgetAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	std::string lastName = widgetAssociateAnEmployeeWithAManagerDialog.getLastName();
	
	company2.AssociateAnEmployeeWithAManager(lastNameManager, lastName);
}

void Widget::SortLastname()
{
	tbl->sortItems(1);

}

void Widget::SortDate()
{
	tbl->sortItems(4);
}

void Widget::GetListAssociate()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	// LeaderEmplyeeChooseDialog 
	GetListAssociateAnEmployeeWithAManagerDialog widgetGetListAssociateAnEmployeeWithAManagerDialog(employees);
	
	widgetGetListAssociateAnEmployeeWithAManagerDialog.resize(100, 110);
	
	if (QDialog::Rejected == widgetGetListAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	std::string lastNameManager = widgetGetListAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	LeaderBehavior* leader = company2.FindLeaderEmployeeByLastName(lastNameManager);
	if (!leader)
	{
//		MsgBox
		return;
	}

	{
		QStringList lst;
	
		lst << toQtString("Должность")
			<< QString::fromLocal8Bit("Фамилия")
			<< QString::fromLocal8Bit("Имя")
			<< QString::fromLocal8Bit("Отчество")
			<< QString::fromLocal8Bit("Дата рождения")
			<< QString::fromLocal8Bit("Дата устройство на работу");

		tbl->setHorizontalHeaderLabels(lst);
	}

	auto submissed = leader->getSubmissed();

//	QEmplyeeListDlg dlg(submissed);
//	dlg.exec();

	QDialog submissedDlg;
	
	EmploeesTableWidget* submissedTbl = new EmploeesTableWidget(submissed, &submissedDlg);
	
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(submissedTbl);

	submissedDlg.setLayout(layout);

	submissedDlg.exec();

	return;



	tbl->setColumnCount(6);

	tbl->setRowCount(submissed.size());

	

	QTableWidgetItem* ptwi = nullptr;

	for (long i = 0; i < submissed.size(); i++)
	{
		
		

			//		std::string stdStr = emplyeesVec[i]->GetPositionName();
			//		const char* cStr = stdStr.c_str();
			//
			//		QString qStr = QString::fromLocal8Bit(cStr);

			ptwi = new QTableWidgetItem(toQtString(submissed[i]->GetPositionName()));
			tbl->setItem(i, 0, ptwi);

			ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetLastName()));
			tbl->setItem(i, 1, ptwi);

			ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetFirstName()));
			tbl->setItem(i, 2, ptwi);

			ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetPatronymic()));
			tbl->setItem(i, 3, ptwi);

			ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetDateOfBirth()));
			tbl->setItem(i, 4, ptwi);

			ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetDateOfHiring()));
			tbl->setItem(i, 5, ptwi);
		}
}
	

void Widget::PrintEmployeeList()
{
	{
		QStringList lst;

		lst << toQtString("Должность")
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
//		std::string stdStr = emplyeesVec[i]->GetPositionName();
//		const char* cStr = stdStr.c_str();
//
//		QString qStr = QString::fromLocal8Bit(cStr);

		ptwi = new QTableWidgetItem(toQtString(emplyeesVec[i]->GetPositionName()));
		tbl->setItem(i, 0, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetLastName()));
		tbl->setItem(i, 1, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetFirstName()));
		tbl->setItem(i, 2, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetPatronymic()));
		tbl->setItem(i, 3, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString( emplyeesVec[i]->GetDateOfBirth()));
		tbl->setItem(i, 4, ptwi);

		ptwi = new QTableWidgetItem(QString::fromStdString(emplyeesVec[i]->GetDateOfHiring()));
		tbl->setItem(i, 5, ptwi);
	}

	
	
}

void Widget::ExitList()
{
	
	ftemp.WriteEmplyeesList(company2);
	
	QApplication::quit();

}
