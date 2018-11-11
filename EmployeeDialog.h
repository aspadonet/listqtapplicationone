#pragma once

#include <QtWidgets/QDialog>

class EmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	EmployeeDialog(QWidget* parent = nullptr);

private slots:
	void onOk();
};
