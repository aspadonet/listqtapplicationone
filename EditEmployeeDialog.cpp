#include "EditEmployeeDialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets>
#include <QMessageBox>
#include "utils.h"

EditEmployeeDialog::EditEmployeeDialog(Employee2* emp, QWidget* parent)
{
	
	empl = emp;
	QVBoxLayout* vBxoLayouot = new QVBoxLayout();

	plblPositionName = new QLabel(QString::fromLocal8Bit("Должность"));

	cbo = new QComboBox();//186


	QString q1 = QString::fromLocal8Bit("Рабочий");
	QString q2 = QString::fromLocal8Bit("Уборщик");
	QString q3 = QString::fromLocal8Bit("Менеджер");
	QString q4 = QString::fromLocal8Bit("Директор");

	cbo->addItem(q1,q1);
	cbo->addItem(q2,q2);
	cbo->addItem(q3,q3);
	cbo->addItem(q4,q4);
	QString cbovalue = (empl->GetPositionName());
	
		
	int index = cbo->findData(cbovalue);
	if (index != -1) { // -1 for not found
		cbo->setCurrentIndex(index);
	}
	plblLastName = new QLabel(QString::fromLocal8Bit("Фамилия"));

	pleLastName = new QLineEdit;
	pleLastName->setText(empl->GetLastName());

	plblFirstName = new QLabel(QString::fromLocal8Bit("Имя"));

	pleFirstName = new QLineEdit;
	pleFirstName->setText(empl->GetFirstName());

	plblPatronymic = new QLabel(QString::fromLocal8Bit("Отчество"));

	plePatronymic = new QLineEdit;
	plePatronymic->setText(empl->GetPatronymic());

	plblDateOfBirth = new QLabel(QString::fromLocal8Bit("Дата рождения"));

	pleDateOfBirth = new QDateEdit;
	pleDateOfBirth->setDate(empl->GetDateOfBirth());

	plblDateOfHiring = new QLabel(QString::fromLocal8Bit("Дата устройство на работу"));

	pleDateOfHiring = new QDateEdit;
	pleDateOfHiring->setDate(empl->GetDateOfHiring());

	QPushButton* okBtn = new QPushButton("Ok");

	//okBtn->setEnabled(false);

	canselBtn = new QPushButton("Cansel");

	QObject::connect(okBtn, &QAbstractButton::clicked, this, &EditEmployeeDialog::onOk);

	QObject::connect(canselBtn, &QAbstractButton::clicked, this, &EditEmployeeDialog::onCansel);

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

void EditEmployeeDialog::onCansel()
{
	reject();
}

void EditEmployeeDialog::onOk()
{

	Position* pos = nullptr;

	QString qstrcbo;

	qstrcbo = cbo->currentText();

	std::string stdWorker = "Рабочий";
	std::string stdCleaner = "Уборщик";
	std::string stdManager = "Менеджер";
	std::string stdDirector = "Директор";
	std::string stdpos = qstrcbo.toLocal8Bit().constData();
	if (empl->GetPositionName() != qstrcbo)
	{
	
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
		empl->SetPositionName(pos);
	}

	if (!pos)
	{
		// _DEBUG_ERROR( "" );
		//return nullptr;
	}

	

	QString lastName = pleLastName->text();

	

	QString firstName = pleFirstName->text();

	

	QString patronymic = plePatronymic->text();

	

	QDate dateOfBirth = pleDateOfBirth->date();

	

	QDate dateOfHiring = pleDateOfHiring->date();

	if (lastName.isEmpty() || firstName.isEmpty() || patronymic.isEmpty())
	{

		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("Заполните все поля"));
		msgBox.exec();
	}
	else
	{
		empl->SetEdit(lastName, firstName, patronymic, dateOfBirth, dateOfHiring);
		accept();
	}





}

