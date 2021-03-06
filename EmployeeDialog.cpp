#include "EmployeeDialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include <QMessageBox>
#include "utils.h"

EmployeeDialog::EmployeeDialog(QWidget* parent)
{
	QVBoxLayout* vBxoLayouot = new QVBoxLayout();
	
	plblPositionName = new QLabel(QString::fromLocal8Bit("���������"));
	
	cbo = new QComboBox();//186
	
	lst << QString::fromLocal8Bit("Worker")
		<< QString::fromLocal8Bit("Cleaner")
		<< QString::fromLocal8Bit("Manager")
		<< QString::fromLocal8Bit("Director");
	
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

	pleDateOfHiring = new QDateEdit;
	

	QPushButton* okBtn = new QPushButton("Ok");

	//okBtn->setEnabled(false);
	
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
	
	std::string stdWorker = "Worker";
	std::string stdCleaner = "Cleaner";
	std::string stdManager = "Manager";
	std::string stdDirector = "Director";
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
		
	QString lastName = pleLastName->text();
	
	qstr = pleFirstName->text();
	
	QString firstName = pleFirstName->text();
	
	qstr = plePatronymic->text();
	
	QString patronymic = plePatronymic->text();
	
	qstr = pleDateOfBirth->date().toString();
	
	QDate dateOfBirth = pleDateOfBirth->date();
	
	qstr = pleDateOfHiring->text();
	
	QDate dateOfHiring = pleDateOfHiring->date();

	if (lastName.isEmpty() || firstName.isEmpty() || patronymic.isEmpty())
	{
		
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("��������� ��� ����"));
		msgBox.exec();
	}
	else
	{
		empl = new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring);
		accept();
	}

	


	
}

Employee2 * EmployeeDialog::getEmploee()
{
	return empl;
}
