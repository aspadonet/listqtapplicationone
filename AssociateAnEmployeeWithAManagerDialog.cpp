#include "AssociateAnEmployeeWithAManagerDialog.h"

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

AssociateAnEmployeeWithAManagerDialog::AssociateAnEmployeeWithAManagerDialog(std::vector< Employee2* > employees, std::vector< Employee2* > employeesLeaders, QWidget* parent)
{
	vBxoLayouot = new QVBoxLayout();
	
	plblText = new QLabel(QString::fromLocal8Bit("Выберите Managerа"));
	//std::vector< Employee2* > emplyeesVec = company2.GetEmployees();
	
	cboEmployee = new QComboBox();
	
	cboPos = new QComboBox();
	
	for (auto it = employeesLeaders.cbegin(); it != employeesLeaders.cend(); it++)
	{
		Employee2* emp2 = *it;

		QString PositionName = emp2->GetPositionName();
		QString LastName = emp2->GetLastName();
		QString FirstName = emp2->GetFirstName();
		QString Patronymic = emp2->GetPatronymic();
		QDate DateOfBirth = emp2->GetDateOfBirth();
		QDate DateOfHiring = emp2->GetDateOfHiring();

		QString result = PositionName + " " + LastName + " " + FirstName + " " + Patronymic + " " + DateOfBirth.toString(Qt::TextDate) + " " + DateOfHiring.toString(Qt::TextDate);
		lst << result;

	}
	
	cboEmployee->addItems(lst);

	plblPositionName = new QLabel(QString::fromLocal8Bit("Выберите подчиненого"));

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
		
		lstPos << result;

	}
	
	cboPos->addItems(lstPos);

	canselBtn = new QPushButton("Cansel");

	addBtn = new QPushButton(QString::fromLocal8Bit("Добавить"));

	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &AssociateAnEmployeeWithAManagerDialog::onCansel);
	QObject::connect(addBtn, &QAbstractButton::clicked, this, &AssociateAnEmployeeWithAManagerDialog::onAdd);
	
	vBxoLayouot->addWidget(plblText);
	vBxoLayouot->addWidget(cboEmployee);
	vBxoLayouot->addWidget(plblPositionName);
	vBxoLayouot->addWidget(cboPos);
	vBxoLayouot->addWidget(addBtn);
	vBxoLayouot->addWidget(canselBtn);
	
	setLayout(vBxoLayouot);

}
void AssociateAnEmployeeWithAManagerDialog::onCansel()
{
	reject();
}

void AssociateAnEmployeeWithAManagerDialog::onAdd()
{
	std::string word;

	QString qstrcboEmployee;
	
	qstrcboEmployee = cboEmployee->currentText();
	
	std::string str = qstrcboEmployee.toLocal8Bit().constData();
	
	std::istringstream iss(str, std::istringstream::in);
	
	std::vector<std::string> wordsVector;
	
	while (iss >> word)
	{
		wordsVector.push_back(word);
	}

	lastNameManager = toQtString(wordsVector[1]);

	std::string word2;
	
	QString qstrcboPos;
	
	qstrcboPos = cboPos->currentText();
	
	std::string stdpos = qstrcboPos.toLocal8Bit().constData();
	
	std::istringstream iss2(stdpos, std::istringstream::in);
	
	std::vector<std::string> wordsVector2;
	
	while (iss2 >> word2)
	{
		wordsVector2.push_back(word2);
	}
	
	lastName = toQtString(wordsVector2[1]);
	
	accept();
}

QString AssociateAnEmployeeWithAManagerDialog::getLastNameManager()
{
	return lastNameManager;
}

QString AssociateAnEmployeeWithAManagerDialog::getLastName()
{
	return lastName;
}



QString AssociateAnEmployeeWithAManagerDialog::toQtString(const std::string& s)
{
	return QString::fromLocal8Bit(s.c_str());
}