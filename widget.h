#pragma once

#include <QtWidgets/QWidget>
#include "Company.h"
#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>
#include <QWidget>
#include <QTableWidget>
#include "Company.h"
#include "EmploeesTableWidget.h"
#include <QFileDialog>
#include <QtSql>


class Widget : public QWidget
{
	Q_OBJECT

private:
	QPushButton* btnAddEmployee; // btnAddEmployee
	QPushButton* btnDelEmployee;
	QPushButton* btnChangePosition;
	QPushButton* btnAssociateEmployee;
	QPushButton* btnSortLastname;
	QPushButton* btnSortDate;
	QPushButton* btnPrintEmployeeList;
	QPushButton* btnGetListAssociate;
	QPushButton* btnExit;
	QMenu* menu = nullptr;
	QMenu* menuBase = nullptr;
	QMenuBar* menuBaseBar;
	const int n = 6;
	QTableWidget*      tbl;//(const int n = 5, const int m = 5);
//	EmploeesTableWidget* tbl;//	EmploeesTableWidget
//	QTableWidgetItem* ptwi = 0;
//	QStringList lst;
	QVBoxLayout* pvbxLayout;
	File2 ftemp;
	std::string strPath = "FileEmplyeesList.txt";
	std::vector< Employee2* > emplyeesVec;


public:
	Widget(QWidget *parent = 0);
	~Widget();

private Q_SLOTS:
	void PrintEmployeeList();
	void AddEmployee();
	void EditEmployee(int row);
	void EditEmployeeCM();
	void DelEmployee();
	void DelEmployeeCM();
	void ChangePosition();
	void AssociateEmployee();
	void SortLastname();
	void SortDate();
	void GetListAssociate();
	void GetListAssociateCM();
	void ExitList();
	void slotCustomMenuRequested(QPoint pos);
	void getOpenFileName();
	void getSaveFileName();
	void SaveFile();
	void SaveXMLFile();
	void ReadXMLFile();
	void SaveSqlFile();
	void ReadSqlFile();
	void tempFromFile(const QString& lastName, std::string pos, const QString& firstName, QString patronymic, const QDate& dateOfBirth, const QDate& dateOfHiring);
	
Q_SIGNALS:
	

private:
	Company2 company2;
	
};

#endif // WIDGET_H