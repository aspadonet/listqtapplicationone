#include "stdafx.h"
#include "EmploeesTableWidget.h"
#include "utils.h"

EmploeesTableWidget::EmploeesTableWidget(std::vector< Employee2* >& emplyeesList, QWidget *parent )
	: QTableWidget( parent )
{
	tbl2 = new QTableWidget(n, n);
	
	tbl2->resize(400, 400);

	//tbl2->setContextMenuPolicy(Qt::CustomContextMenu);
	
	//QObject::connect(tbl2, &QMenu::customContextMenuRequested, this, &EmploeesTableWidget::slotCustomMenuRequested);
	

	pvbxLayout = new QVBoxLayout;
	pvbxLayout->addWidget(tbl2);
	

	setLayout(pvbxLayout);
	

	 emplyeesVec = emplyeesList;//company2.GetEmployees();
	 PrintEmployeeList();
	
	}

//void EmploeesTableWidget::slotCustomMenuRequested(QPoint pos)
//{
//	 
//	menu = new QMenu(this);
//	 
//	QAction * editDevice = new QAction(toQtString("Редактировать"), this);
//	QAction * deleteDevice = new QAction(toQtString("Удалить"), this);
//
//	connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
//	//QObject::connect(editDevice, &QAction::triggered, , &Widget::AddEmployee);
//	menu->addAction(editDevice);
//	menu->addAction(deleteDevice);
//	 
//	menu->popup(tbl2->viewport()->mapToGlobal(pos));
//}

	void EmploeesTableWidget::PrintEmployeeList()
	{
		{
			QStringList lst;

			lst << toQtString("Должность")
				<< QString::fromLocal8Bit("Фамилия")
				<< QString::fromLocal8Bit("Имя")
				<< QString::fromLocal8Bit("Отчество")
				<< QString::fromLocal8Bit("Дата рождения")
				<< QString::fromLocal8Bit("Дата устройство на работу");

			tbl2->setHorizontalHeaderLabels(lst);
		}

		
		tbl2->setColumnCount(6);

		tbl2->setRowCount(emplyeesVec.size());

		QTableWidgetItem* ptwi = nullptr;

		for (int i = 0; i < emplyeesVec.size(); ++i) {


			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPositionName());
			tbl2->setItem(i, 0, ptwi);

			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetLastName());
			tbl2->setItem(i, 1, ptwi);

			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetFirstName());
			tbl2->setItem(i, 2, ptwi);

			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPatronymic());
			tbl2->setItem(i, 3, ptwi);

			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfBirth().toString(Qt::TextDate));
			tbl2->setItem(i, 4, ptwi);

			ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfHiring().toString(Qt::TextDate));
			tbl2->setItem(i, 5, ptwi);
	}
}
