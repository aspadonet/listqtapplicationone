#include "EmployeeDialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include "utils.h"

EmployeeDialog::EmployeeDialog(QWidget* parent)
{
	QVBoxLayout* vBxoLayouot = new QVBoxLayout();
	
	plblPositionName = new QLabel(QString::fromLocal8Bit("���������"));
	
	cbo = new QComboBox();//186
	
	lst << QString::fromLocal8Bit("�������")
		<< QString::fromLocal8Bit("�������")
		<< QString::fromLocal8Bit("��������")
		<< QString::fromLocal8Bit("��������");
	
	cbo->addItems(lst);
	
	plblLastName = new QLabel(QString::fromLocal8Bit("�������"));

	pleLastName = new QLineEdit;

	plblFirstName = new QLabel(QString::fromLocal8Bit("���"));

	pleFirstName = new QLineEdit;

	plblPatronymic = new QLabel(QString::fromLocal8Bit("��������"));

	plePatronymic = new QLineEdit;

	plblDateOfBirth = new QLabel(QString::fromLocal8Bit("���� ��������"));

	pleDateOfBirth = new QDateEdit;

	plblDateOfHiring = new QLabel(QString::fromLocal8Bit("���� ���������� �� ������"));

	pleDateOfHiring = new QLineEdit;
	

	QPushButton* okBtn = new QPushButton("Ok");
	
	canselBtn = new QPushButton("Cansel");
	
	QObject::connect(okBtn, &QAbstractButton::clicked, this, &EmployeeDialog::onOk);
	
	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &EmployeeDialog::onCansel);
	
	vBxoLayouot->addWidget(plblPositionName);
	vBxoLayouot->addWidget(cbo);
	vBxoLayouot->addWidget(plblLastName);
	vBxoLayouot->addWidget(pleLastName);
	vBxoLayouot->addWidget(plblFirstName);
	vBxoLayouot->addWidget(pleFirstName);
	vBxoLayouot->addWidget(plblPatronymic);
	vBxoLayouot->addWidget(plePatronymic);
	vBxoLayouot->addWidget(plblDateOfBirth);
	vBxoLayouot->addWidget(pleDateOfBirth);
	vBxoLayouot->addWidget(plblDateOfHiring);
	vBxoLayouot->addWidget(pleDateOfHiring);
	
	vBxoLayouot->addWidget(okBtn);
	vBxoLayouot->addWidget(canselBtn);
	
	setLayout(vBxoLayouot);
}

void EmployeeDialog::onCansel()
{
	reject();
}

void EmployeeDialog::onOk()
{
	
	Position* pos = nullptr;
	
	QString qstrcbo;
	
	qstrcbo= cbo->currentText();
	
	std::string stdWorker = "�������";
	std::string stdCleaner = "�������";
	std::string stdManager = "��������";
	std::string stdDirector = "��������";
	std::string stdpos = qstrcbo.toLocal8Bit().constData();
	
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


	if (!pos)
	{
		// _DEBUG_ERROR( "" );
		//return nullptr;
	}
	
	QString qstr;
	
	qstr= pleLastName->text();
	
	std::string lastName = qstr.toStdString();
	
	qstr = pleFirstName->text();
	
	std::string firstName = qstr.toStdString();
	
	qstr = plePatronymic->text();
	
	std::string patronymic = qstr.toStdString();
	
	qstr = pleDateOfBirth->date().toString();
	
	std::string dateOfBirth = qstr.toStdString();
	
	qstr = pleDateOfHiring->text();
	
	std::string dateOfHiring = qstr.toStdString();

	empl =  new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring);


	accept();
}

Employee2 * EmployeeDialog::getEmploee()
{
	return empl;
}
