#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"

class EditEmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	EditEmployeeDialog(Employee2* emp, QWidget* parent = nullptr);
	
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
	QDateEdit* pleDateOfHiring;
	QPushButton* okBtn;
	QPushButton* canselBtn;
	QComboBox* cbo;
	QStringList lst;
private slots:
	void onCansel();
	void onOk();
};
