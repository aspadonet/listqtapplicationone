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
	
	btnAddEmployee = new QPushButton(QString::fromLocal8Bit("&добавить сотрудника"));
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
	menuBaseBar = new QMenuBar;
	menuBase = new QMenu("&Menu");
	menuBaseBar->addMenu(menuBase);

	menuBase->addAction(QString::fromLocal8Bit("Загрузить из файла"), this, &Widget::getOpenFileName);
	menuBase->addAction(QString::fromLocal8Bit("Сохранить в файл"), this, &Widget::DelEmployee);
	
	menuBase->addSeparator();
	
	QMenu* subMenuBaseSort = new QMenu(QString::fromLocal8Bit("Сортировать"), menuBase);
	menuBase->addMenu(subMenuBaseSort);
	subMenuBaseSort->addAction(QString::fromLocal8Bit("&сортировать список по фамилиям"),this, &Widget::SortLastname);
	subMenuBaseSort->addAction(QString::fromLocal8Bit("&сортировать датам принятия на работу"), this, &Widget::SortDate);
	menuBase->addSeparator();
	menuBase->addAction(QString::fromLocal8Bit("Выход"), this, &Widget::ExitList);

	
	//menuBaseBar.show();
	
	ftemp.ReadEmplyeesList(company2);
	tbl= new QTableWidget(n, n);
	//tbl->setModel(modelDevice);
	//tbl->setColumnHidden(0, true);
	tbl->setSelectionBehavior(QAbstractItemView::SelectRows);
	/*tbl->setSelectionMode(QAbstractItemView::SingleSelection);*/
	//tbl->resizeColumnsToContents();
	tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//tbl->horizontalHeader()->setStretchLastSection(true);
	tbl->resize(400, 400);

	tbl->setContextMenuPolicy(Qt::CustomContextMenu);

	QObject::connect(tbl, &QMenu::customContextMenuRequested, this, &Widget::slotCustomMenuRequested);
	QObject::connect(tbl, &QTableWidget::doubleClicked, this, &Widget::GetListAssociateCM);

	pvbxLayout = new QVBoxLayout;
	//pvbxLayout->setMenuBar(menuBase);
	//pvbxLayout->addWidget(menuBase);
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
	layout()->setMenuBar(menuBaseBar);
	//ftemp.ReadEmplyeesList(company2);
//	tbl->PrintEmployeeList(); //	EmploeesTableWidget
	PrintEmployeeList();
}

Widget::~Widget()
{
}

void Widget::slotCustomMenuRequested(QPoint pos)
{
	QTableWidgetItem* item = tbl->itemAt( pos );
	if (!item)
		return;

	int emplyeeIndex = item->row();
//	Employee2* curentEmp = emplyeesVec[row];

	QMenu* popupMenu = new QMenu(this);

	QAction * editDevice = new QAction(toQtString("Редактировать"), this);
	QAction * deleteDevice = new QAction(toQtString("Удалить"), this);
	
//	QObject::connect(editDevice, &QAction::triggered, this, [ emplyeeIndex ]()
//	{
//		EditEmployee( emplyeeIndex );
//	} );

	QObject::connect(deleteDevice, &QAction::triggered, this, &Widget::DelEmployeeCM);

	popupMenu->addAction(editDevice);
	popupMenu->addAction(deleteDevice);

	QPoint globalPos = tbl->viewport()->mapToGlobal(pos);
	popupMenu->popup( globalPos );
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

	QString lastName = widgetDeleteEmployee.getLastName();
	
	company2.DeleteEmployee2(lastName);

	//widgetDeleteEmployeeDialog.show();
}

void Widget::DelEmployeeCM()
{
	int row = tbl->selectionModel()->currentIndex().row();

	QTableWidgetItem* lastNameitem = tbl->item(row, 1);

	QString lastName = lastNameitem->text();
	
	company2.DeleteEmployee2(lastName);
}

void Widget::ChangePosition()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	ChangePositionDialog widgetChangePositionDialog(employees);
	
	widgetChangePositionDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetChangePositionDialog.exec())
		return;

	QString lastName = widgetChangePositionDialog.getLastName();
	
	Position* pos = widgetChangePositionDialog.getPositionName();
	
	company2.ChangePosition(lastName, pos);
}

void Widget::AssociateEmployee()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	AssociateAnEmployeeWithAManagerDialog widgetAssociateAnEmployeeWithAManagerDialog(employees);
	
	widgetAssociateAnEmployeeWithAManagerDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	QString lastNameManager = widgetAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	QString lastName = widgetAssociateAnEmployeeWithAManagerDialog.getLastName();
	
	company2.AssociateAnEmployeeWithAManager(lastNameManager, lastName);
}

void Widget::SortLastname()
{
	tbl->sortItems(1);

}

void Widget::SortDate()
{
	tbl->sortItems(5);
}

void Widget::GetListAssociate()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	// LeaderEmplyeeChooseDialog 
	GetListAssociateAnEmployeeWithAManagerDialog widgetGetListAssociateAnEmployeeWithAManagerDialog(employees);
	
	widgetGetListAssociateAnEmployeeWithAManagerDialog.resize(100, 110);
	
	if (QDialog::Rejected == widgetGetListAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	QString lastNameManager = widgetGetListAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	LeaderBehavior* leader = company2.FindLeaderEmployeeByLastName(lastNameManager);
	if (!leader)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("нет подчинёных!!!"));
		msgBox.exec();

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

			ptwi = new QTableWidgetItem(submissed[i]->GetPositionName());
			tbl->setItem(i, 0, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetLastName());
			tbl->setItem(i, 1, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetFirstName());
			tbl->setItem(i, 2, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetPatronymic());
			tbl->setItem(i, 3, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetDateOfBirth().toString(Qt::ISODate));
			tbl->setItem(i, 4, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetDateOfHiring().toString(Qt::ISODate));
			tbl->setItem(i, 5, ptwi);
		}
}
void Widget::GetListAssociateCM()
{
	std::vector< Employee2* > employees = company2.GetEmployees();

	int row = tbl->selectionModel()->currentIndex().row();

	QTableWidgetItem *	lastNameitem;

	lastNameitem = tbl->item(row, 1);
	lastNameitem->text();

	QString lastName = lastNameitem->text();
	QString lastNameManager = lastName;

	LeaderBehavior* leader = company2.FindLeaderEmployeeByLastName(lastNameManager);
	if (!leader)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("нет подчинёных!!!"));
		msgBox.exec();
	
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

	submissedDlg.resize(800, 800);

	EmploeesTableWidget* submissedTbl = new EmploeesTableWidget(submissed, &submissedDlg);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(submissedTbl);

	submissedDlg.setLayout(layout);

	submissedDlg.exec();

	return;


	//tbl->setColumnCount(6);

	//tbl->setRowCount(submissed.size());



	//QTableWidgetItem* ptwi = nullptr;

	//for (long i = 0; i < submissed.size(); i++)
	//{



	//	//		std::string stdStr = emplyeesVec[i]->GetPositionName();
	//	//		const char* cStr = stdStr.c_str();
	//	//
	//	//		QString qStr = QString::fromLocal8Bit(cStr);

	//	ptwi = new QTableWidgetItem(toQtString(submissed[i]->GetPositionName()));
	//	tbl->setItem(i, 0, ptwi);

	//	ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetLastName()));
	//	tbl->setItem(i, 1, ptwi);

	//	ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetFirstName()));
	//	tbl->setItem(i, 2, ptwi);

	//	ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetPatronymic()));
	//	tbl->setItem(i, 3, ptwi);

	//	ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetDateOfBirth()));
	//	tbl->setItem(i, 4, ptwi);

	//	ptwi = new QTableWidgetItem(QString::fromStdString(submissed[i]->GetDateOfHiring()));
	//	tbl->setItem(i, 5, ptwi);
	//}
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
//		QString stdStr = emplyeesVec[i]->GetPositionName();
//		const char* cStr = stdStr.c_str();
//
//		QString qStr = QString::fromLocal8Bit(cStr);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPositionName());
		tbl->setItem(i, 0, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetLastName());
		tbl->setItem(i, 1, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetFirstName());
		tbl->setItem(i, 2, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPatronymic());
		tbl->setItem(i, 3, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfBirth().toString(Qt::ISODate));
		tbl->setItem(i, 4, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfHiring().toString(Qt::ISODate));
		tbl->setItem(i, 5, ptwi);
	}

	
	
}

void Widget::getOpenFileName()
{
	QString str = QFileDialog::getOpenFileName(this, "Open Dialog", QDir::currentPath(), "");

}

void Widget::ExitList()
{
	
	ftemp.WriteEmplyeesList(company2);
	
	QApplication::quit();

}
