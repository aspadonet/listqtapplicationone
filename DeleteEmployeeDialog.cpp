#include "DeleteEmployeeDialog.h"
//#include "Company.h"
//#include "utils.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

DeleteEmployeeDialog::DeleteEmployeeDialog(std::vector< Employee2* > employees, QWidget* parent)
{
	vBxoLayouot = new QVBoxLayout();
	
	plblText = new QLabel(QString::fromLocal8Bit("Выберите сотрудника для удаления"));
	
	//std::vector< Employee2* > emplyeesVec = company2.GetEmployees();
	
	cbo = new QComboBox();
	
	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* emp2 = *it;
		
		QString PositionName = toQtString(emp2->GetPositionName());
		QString LastName = emp2->GetLastName();
		QString FirstName = toQtString(emp2->GetFirstName());
		QString Patronymic = toQtString(emp2->GetPatronymic());
		QString DateOfBirth = toQtString(emp2->GetDateOfBirth());
		QString DateOfHiring = toQtString(emp2->GetDateOfHiring());

		QString result =PositionName + " " + LastName + " " + FirstName + " " + Patronymic + " " + DateOfBirth + " " + DateOfHiring;
		
		lst << result;
		
	}
	
	cbo->addItems(lst);

	canselBtn = new QPushButton("Cansel");

	deleteBtn = new QPushButton(QString::fromLocal8Bit("Удалить"));
	
	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &DeleteEmployeeDialog::onCansel);
	QObject::connect(deleteBtn, &QAbstractButton::clicked, this, &DeleteEmployeeDialog::onDelete);
	
	vBxoLayouot->addWidget(cbo);
	vBxoLayouot->addWidget(deleteBtn);
	vBxoLayouot->addWidget(canselBtn);
	
	setLayout(vBxoLayouot);

}
void DeleteEmployeeDialog::onCansel()
{
	reject();
}

void DeleteEmployeeDialog::onDelete()
{
	std::string word;
	
	QString qstrcbo;
	
	qstrcbo = cbo->currentText();
	
	std::string str = qstrcbo.toLocal8Bit().constData();
	
	std::istringstream iss(str, std::istringstream::in);
	
	std::vector<std::string> wordsVector;
	
	while (iss >> word)
	{
		wordsVector.push_back(word);
	}
	   
	lastName = toQtString(wordsVector[1]);
	
	accept();
	
}

QString DeleteEmployeeDialog::getLastName()
{
	return lastName;
}

QString DeleteEmployeeDialog::toQtString(const std::string& s)
{
	return QString::fromLocal8Bit(s.c_str());
}