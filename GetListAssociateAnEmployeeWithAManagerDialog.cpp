#include "GetListAssociateAnEmployeeWithAManagerDialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

GetListAssociateAnEmployeeWithAManagerDialog::GetListAssociateAnEmployeeWithAManagerDialog(std::vector< Employee2* > employees, QWidget* parrent)
{
	vBxoLayouot = new QVBoxLayout();
	
	plblText = new QLabel(QString::fromLocal8Bit("Выберите менеджера"));
	
	//std::vector< Employee2* > emplyeesVec = company2.GetEmployees();
	
	cboEmployee = new QComboBox();
	
	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* emp2 = *it;

		QString PositionName = emp2->GetPositionName();
		QString LastName = emp2->GetLastName();
		QString FirstName = emp2->GetFirstName();
		QString Patronymic = emp2->GetPatronymic();
		QDate DateOfBirth = emp2->GetDateOfBirth();
		QDate DateOfHiring = emp2->GetDateOfHiring();
		
		QString result = PositionName + " " + LastName + " " + FirstName + " " + Patronymic + " " + DateOfBirth.toString(Qt::TextDate) + " " + DateOfHiring.toString(Qt::TextDate);

		cboEmployee->addItem(result, LastName);
	}
	
	canselBtn = new QPushButton("Cancel");

	okBtn = new QPushButton("Ok");

	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &GetListAssociateAnEmployeeWithAManagerDialog::onCansel);
	QObject::connect(okBtn, &QAbstractButton::clicked, this, &GetListAssociateAnEmployeeWithAManagerDialog::onOk);
	
	vBxoLayouot->addWidget(plblText);
	vBxoLayouot->addWidget(cboEmployee);
	vBxoLayouot->addWidget(okBtn);
	vBxoLayouot->addWidget(canselBtn);
	
	setLayout(vBxoLayouot);
}


void GetListAssociateAnEmployeeWithAManagerDialog::onOk()
{
	lastNameManager = cboEmployee->currentData().toString();
	accept();
}

QString GetListAssociateAnEmployeeWithAManagerDialog::getLastNameManager()
{
	return lastNameManager;
}

void GetListAssociateAnEmployeeWithAManagerDialog::onCansel()
{
	reject();
}

QString GetListAssociateAnEmployeeWithAManagerDialog::toQtString(const std::string& s)
{
	return QString::fromLocal8Bit(s.c_str());
}