#include "ChangePositionDialog.h"
//#include "Company.h"

#include "utils.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

ChangePositionDialog::ChangePositionDialog(std::vector< Employee2* > employees, QWidget* parent)
{
	
	vBxoLayouot = new QVBoxLayout();
	
	plblText = new QLabel(QString::fromLocal8Bit("Выберите сотрудника для удаления"));
	
	//std::vector< Employee2* > emplyeesVec = company2.GetEmployees();
	
	cboEmployee = new QComboBox();
	
	cboPos = new QComboBox();
	
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
		lst << result;




	}
	cboEmployee->addItems(lst);

	plblPositionName = new QLabel(QString::fromLocal8Bit("Новая должность"));

	lstPos << QString::fromLocal8Bit("Worker")
		<< QString::fromLocal8Bit("Cleaner")
		<< QString::fromLocal8Bit("Manager")
		<< QString::fromLocal8Bit("Director");
	cboPos->addItems(lstPos);

	canselBtn = new QPushButton("Cansel");

	changeBtn = new QPushButton(QString::fromLocal8Bit("Изменить"));

	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &ChangePositionDialog::onCansel);
	
	QObject::connect(changeBtn, &QAbstractButton::clicked, this, &ChangePositionDialog::onChange);
	
	vBxoLayouot->addWidget(plblText);
	vBxoLayouot->addWidget(cboEmployee);
	vBxoLayouot->addWidget(plblPositionName);
	vBxoLayouot->addWidget(cboPos);
	vBxoLayouot->addWidget(changeBtn);
	vBxoLayouot->addWidget(canselBtn);
	
	setLayout(vBxoLayouot);

}
void ChangePositionDialog::onCansel()
{
	reject();
}

void ChangePositionDialog::onChange()
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

	lastName = toQtString( wordsVector[1] );

	QString qstrcboPos;
	
	qstrcboPos = cboPos->currentText();
	
	std::string stdWorker = "Worker";
	std::string stdCleaner = "Cleaner";
	std::string stdManager = "Manager";
	std::string stdDirector = "Director";
	
	std::string stdpos = qstrcboPos.toLocal8Bit().constData();
	
	if (stdpos == stdWorker)
	{
		pos = new WorkerPosition();
	}
	
	else if (stdpos == stdCleaner)
	{
		pos = new CleanerPosition();
	}
	
	else if (stdpos == stdManager)
	{
		pos = new ManagerPosition();
	}
	
	else if (stdpos == stdDirector)
	{
		pos = new DirectorPosition();
	}
	
	else
	{
		pos = new WorkerPosition();
	}

	accept();
}

QString ChangePositionDialog::getLastName()
{
	return lastName;
}

Position* ChangePositionDialog::getPositionName()
{
	return pos;
}

/*QString ChangePositionDialog::toQtString(const std::string& s)
{
	return QString::fromLocal8Bit(s.c_str());
}*/