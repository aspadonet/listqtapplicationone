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

class Widget : public QWidget
{

	Q_OBJECT
private:
	QPushButton* ADD_EMPLOYEE;
	QPushButton* DEL_EMPLOYEE;
	QPushButton* CHANGE_POSITION;
	QPushButton* ASSOCIATE_EMPLOYEE;
	QPushButton* SORT_LASTNAME;
	QPushButton* SORT_DATE;
	QPushButton* PRINT_EMPLYEES_LIST;
	QPushButton* GET_LIST_ASSOCIATE;
	QPushButton* EXIT;
	const int n = 6;
	QTableWidget*      tbl;//(const int n = 5, const int m = 5);
	QTableWidgetItem* ptwi = 0;
	QStringList lst;
	QVBoxLayout* pvbxLayout;
public:
	Widget(QWidget *parent = 0);
	~Widget();
private Q_SLOTS:
	void PRINT_EMPLYEES_LISTBtnClicked();
	

Q_SIGNALS:
	void calculatedNewResult(QString result);
};

#endif // WIDGET_H