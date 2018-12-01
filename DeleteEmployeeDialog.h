#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"
//#include "utils.h"


class DeleteEmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	DeleteEmployeeDialog(std::vector< Employee2* > employees,QWidget* parrent = nullptr);
	QString toQtString(const std::string& s);
	std::string getLastName();
private:
	Company2 company2;
	Employee2* empl;
	QLabel* plblText;
	QPushButton* deleteBtn;
	QPushButton* canselBtn;
	QComboBox* cbo;
	QStringList lst;
	QVBoxLayout* vBxoLayouot;
	std::string lastName;
private slots:
	void onCansel();
	void onDelete();
};
