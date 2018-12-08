#pragma once
#include "QTableWidget"
#include "Employee.h"
#include <QtWidgets>
//#include "Widget.h"

class EmploeesTableWidget : public QTableWidget
{
public:
	EmploeesTableWidget( std::vector< Employee2* >& emplyeesList, QWidget *parent = nullptr);
	void PrintEmployeeList();
private:
	QTableWidget* tbl2;
	QMenu* menu = nullptr;
	const int n = 6;
	std::vector< Employee2* > emplyeesVec;
	QVBoxLayout* pvbxLayout;
	private Q_SLOTS:
	void slotCustomMenuRequested(QPoint pos);
};
