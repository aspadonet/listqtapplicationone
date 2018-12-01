#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"

class EmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	EmployeeDialog(QWidget* parent = nullptr);
	Employee2* getEmploee();
	
private:
	Employee2* empl;
	QLabel* plblPositionName;
	QLabel* plblLastName;
	QLineEdit* pleLastName;
	QLabel* plblFirstName;
	QLineEdit* pleFirstName;
	QLabel* plblPatronymic;
	QLineEdit* plePatronymic;
	QLabel* plblDateOfBirth;
	QDateEdit* pleDateOfBirth;
	QLabel* plblDateOfHiring;
	QLineEdit* pleDateOfHiring;
	QPushButton* okBtn;
	QPushButton* canselBtn;
	QComboBox* cbo;
	QStringList lst;
private slots:
	void onCansel();
	void onOk();
};
