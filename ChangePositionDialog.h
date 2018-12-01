#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"
//#include "utils.h"


class ChangePositionDialog : public QDialog
{
	Q_OBJECT

public:
	ChangePositionDialog(std::vector< Employee2* > employees, QWidget* parrent = nullptr);
//	QString toQtString(const std::string& s);
	std::string getLastName();
	Position* getPositionName();
private:
	Employee2* empl;
	Position* pos = nullptr;
	QLabel* plblText;
	QLabel* plblPositionName;
	QLabel* plblLastName;
	QPushButton* changeBtn;
	QPushButton* canselBtn;
	QComboBox* cboEmployee;
	QComboBox* cboPos;
	QStringList lst;
	QStringList lstPos;
	QVBoxLayout* vBxoLayouot;
	std::string lastName;
private slots:
	void onCansel();
	void onChange();
};