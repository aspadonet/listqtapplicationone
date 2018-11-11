#include "EmployeeDialog.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

EmployeeDialog::EmployeeDialog(QWidget* parent)
{
	QVBoxLayout* vBxoLayouot = new QVBoxLayout();

	QPushButton* okBtn = new QPushButton("Ok");
	QObject::connect(okBtn, &QAbstractButton::clicked, this, &EmployeeDialog::onOk);

	vBxoLayouot->addWidget(okBtn);

	setLayout(vBxoLayouot);
}


void EmployeeDialog::onOk()
{
	accept();
}
