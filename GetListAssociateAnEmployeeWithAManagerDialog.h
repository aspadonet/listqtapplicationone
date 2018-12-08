#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"

class GetListAssociateAnEmployeeWithAManagerDialog : public QDialog
{
	Q_OBJECT;
public:
	GetListAssociateAnEmployeeWithAManagerDialog(std::vector< Employee2* > employees, QWidget* parrent = nullptr);
	QString toQtString(const std::string& s);
	QString getLastNameManager();
private:
	Employee2* empl;
	Position* pos = nullptr;
	QLabel* plblText;
	QLabel* plblLastName;
	QPushButton* okBtn;
	QPushButton* canselBtn;
	QComboBox* cboEmployee;
//	QStringList lst;
	QVBoxLayout* vBxoLayouot;
	QString lastNameManager;

	std::vector< QString > lastNames;
private slots:
	void onCansel();
	void onOk();
};
