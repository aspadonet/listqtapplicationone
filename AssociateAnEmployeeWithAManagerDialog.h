#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"
//#include "utils.h"


class AssociateAnEmployeeWithAManagerDialog : public QDialog
{
	Q_OBJECT

public:
	AssociateAnEmployeeWithAManagerDialog(std::vector< Employee2* > employees, std::vector< Employee2* > employeesLeaders, QWidget* parrent = nullptr);
	QString toQtString(const std::string& s);
	QString getLastNameManager();
	QString getLastName();
private:
	Employee2* empl;
	Position* pos = nullptr;
	QLabel* plblText;
	QLabel* plblPositionName;
	QLabel* plblLastName;
	QPushButton* addBtn;
	QPushButton* canselBtn;
	QComboBox* cboEmployee;
	QComboBox* cboPos;
	QStringList lst;
	QStringList lstPos;
	QVBoxLayout* vBxoLayouot;
	QString lastNameManager;
	QString lastName;
private slots:
	void onCansel();
	void onAdd();
};