#pragma once

#include <QtWidgets/QWidget>
#include "Company.h"

//class listqtapplicationone : public QWidget
//{
//	Q_OBJECT
//
//public:
//	listqtapplicationone(QWidget *parent = Q_NULLPTR);
//
//private:
//	
//};
#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>
#include <QWidget>
#include <QTableWidget>
#include "Company.h"

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
	const int n = 6;
	QTableWidget*      tbl;//(const int n = 5, const int m = 5);
//	QTableWidgetItem* ptwi = 0;
//	QStringList lst;
	QVBoxLayout* pvbxLayout;
	File2 ftemp;
public:
	Widget(QWidget *parent = 0);
	~Widget();

private Q_SLOTS:
	void PrintEmployeeList();
	void AddEmployee();
	void DelEmployee();
	void ChangePosition();
	void AssociateEmployee();
	void SortLastname();
	void SortDate();
	void GetListAssociate();
	void ExitList();

Q_SIGNALS:
	

private:
	Company2 company2;
	
};

#endif // WIDGET_H