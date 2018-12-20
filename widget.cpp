#include "stdafx.h"

#include "widget.h"
#include <QtWidgets>

#include "utils.h"
#include <QFile>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include <QXmlStreamWriter>
#include "Employee.h"
#include "File.h"
#include "Position.h"

#include "EmployeeDialog.h"
#include "EditEmployeeDialog.h"
#include "DeleteEmployeeDialog.h"
#include "ChangePositionDialog.h"
#include "AssociateAnEmployeeWithAManagerDialog.h"
#include "GetListAssociateAnEmployeeWithAManagerDialog.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
Widget::Widget(QWidget *parent)
	: QWidget(parent)
{	
	
	btnAddEmployee = new QPushButton(QString::fromLocal8Bit("&добавить сотрудника"));
	btnDelEmployee = new QPushButton(QString::fromLocal8Bit("&удалить сотрудника"));
	btnChangePosition = new QPushButton(QString::fromLocal8Bit("&изменить тип сотрудника"));
	btnAssociateEmployee = new QPushButton(QString::fromLocal8Bit("&привязывать сотрудника к менеджеру"));
	btnSortLastname = new QPushButton(QString::fromLocal8Bit("&сортировать список по фамилиям"));
	btnSortDate = new QPushButton(QString::fromLocal8Bit("&сортировать датам принятия на работу"));
	btnPrintEmployeeList = new QPushButton(QString::fromLocal8Bit("&вывести список работников"));
	btnGetListAssociate = new QPushButton(QString::fromLocal8Bit("&вывести список работников привязаных к менеджеру"));
	btnExit = new QPushButton(QString::fromLocal8Bit("&Сохранить изменения и завершить работу"));

	//QObject::connect(btnExit, &QPushButton::clicked, &a, &a::quit());
	QObject::connect(btnDelEmployee, &QPushButton::clicked, this, &Widget::DelEmployee);
	QObject::connect(btnAddEmployee, &QPushButton::clicked, this, &Widget::AddEmployee);
	QObject::connect(btnChangePosition, &QPushButton::clicked, this, &Widget::ChangePosition);
	QObject::connect(btnAssociateEmployee, &QPushButton::clicked, this, &Widget::AssociateEmployee);
	QObject::connect(btnSortLastname, &QPushButton::clicked, this, &Widget::SortLastname);
	QObject::connect(btnSortDate, &QPushButton::clicked, this, &Widget::SortDate);
	QObject::connect(btnPrintEmployeeList, &QPushButton::clicked, this, &Widget::PrintEmployeeList);
	QObject::connect(btnGetListAssociate, &QPushButton::clicked, this, &Widget::GetListAssociate);
	QObject::connect(btnExit, &QPushButton::clicked, this, &Widget::ExitList);
	
		
	menuBaseBar = new QMenuBar;

	menuBase = new QMenu("&Menu");

	menuBaseBar->addMenu(menuBase);

	menuBase->addAction(QString::fromLocal8Bit("Загрузить из файла *.txt"), this, &Widget::getOpenFileName);
	menuBase->addAction(QString::fromLocal8Bit("Сохранить в файл *.txt"), this, &Widget::getSaveFileName);

	menuBase->addAction(QString::fromLocal8Bit("Сохранить изменения в *.txt"), this, &Widget::SaveFile);

	menuBase->addSeparator();
	
	menuBase->addAction(QString::fromLocal8Bit("Загрузить из файла *.xml"), this, &Widget::ReadXMLFile);
	menuBase->addAction(QString::fromLocal8Bit("Сохранить в файл *.xml"), this, &Widget::SaveXMLFile);
	

	//menuBase->addSeparator();

	//menuBase->addAction(QString::fromLocal8Bit("Загрузить из файла *.xml"), this, &Widget::ReadSqlFile);
	//menuBase->addAction(QString::fromLocal8Bit("Сохранить в файл *.xml"), this, &Widget::SaveSqlFile);


	menuBase->addSeparator();
	
	QMenu* subMenuBaseSort = new QMenu(QString::fromLocal8Bit("Сортировать"), menuBase);
	menuBase->addMenu(subMenuBaseSort);
	
	subMenuBaseSort->addAction(QString::fromLocal8Bit("&сортировать список по фамилиям"),this, &Widget::SortLastname);
	subMenuBaseSort->addAction(QString::fromLocal8Bit("&сортировать датам принятия на работу"), this, &Widget::SortDate);
	
	menuBase->addSeparator();
	
	menuBase->addAction(QString::fromLocal8Bit("Выход"), this, &Widget::ExitList);

	
	//menuBaseBar.show();
	
	ftemp.ReadEmplyeesList(company2);
	
	tbl= new QTableWidget(n, n);
	//tbl->setModel(modelDevice);
	//tbl->setColumnHidden(0, true);
	tbl->setSelectionBehavior(QAbstractItemView::SelectRows);
	/*tbl->setSelectionMode(QAbstractItemView::SingleSelection);*/
	//tbl->resizeColumnsToContents();
	tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//tbl->horizontalHeader()->setStretchLastSection(true);
	tbl->resize(400, 400);

	tbl->setContextMenuPolicy(Qt::CustomContextMenu);

	QObject::connect(tbl, &QMenu::customContextMenuRequested, this, &Widget::slotCustomMenuRequested);
	QObject::connect(tbl, &QTableWidget::cellDoubleClicked, this, &Widget::EditEmployee);

	pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(tbl);
	pvbxLayout->addWidget(btnAddEmployee);
	pvbxLayout->addWidget(btnDelEmployee);
	pvbxLayout->addWidget(btnChangePosition);
	pvbxLayout->addWidget(btnAssociateEmployee);
	pvbxLayout->addWidget(btnSortLastname);
	pvbxLayout->addWidget(btnSortDate);
	pvbxLayout->addWidget(btnPrintEmployeeList);
	pvbxLayout->addWidget(btnGetListAssociate);
	pvbxLayout->addWidget(btnExit);
	
	setLayout(pvbxLayout);

	layout()->setMenuBar(menuBaseBar);
	//ftemp.ReadEmplyeesList(company2);
//	tbl->PrintEmployeeList(); //	EmploeesTableWidget
	PrintEmployeeList();
}

Widget::~Widget()
{
}

void Widget::slotCustomMenuRequested(QPoint pos)
{
	QTableWidgetItem* item = tbl->itemAt( pos );
	
	if (!item)
		return;

	int emplyeeIndex = item->row();
//	Employee2* curentEmp = emplyeesVec[row];

	QMenu* popupMenu = new QMenu(this);

	QAction * editDevice = new QAction(toQtString("Редактировать"), this);
	
	QAction * deleteDevice = new QAction(toQtString("Удалить"), this);
	
//	QObject::connect(editDevice, &QAction::triggered, this, [ emplyeeIndex ]()
//	{
//		EditEmployee( emplyeeIndex );
//	} );
	QObject::connect(editDevice, &QAction::triggered, this, &Widget::EditEmployeeCM);
	
	QObject::connect(deleteDevice, &QAction::triggered, this, &Widget::DelEmployeeCM);

	popupMenu->addAction(editDevice);
	
	popupMenu->addAction(deleteDevice);

	QPoint globalPos = tbl->viewport()->mapToGlobal(pos);
	
	popupMenu->popup( globalPos );
}

void Widget::AddEmployee()
{
	EmployeeDialog widgetAddEmployee;

	widgetAddEmployee.resize(100,100);

	//int res = widgetAddEmployee.exec();
	//long sdf = 789;

	if (QDialog::Rejected == widgetAddEmployee.exec())
		return;

	Employee2* emp = widgetAddEmployee.getEmploee();
	
	company2.AddEmployee( emp );

//	widgetAddEmployee.leName.getText();
//	Employee2 emp = widgetAddEmployee.getEmploee();
	
	PrintEmployeeList();
}

void Widget::EditEmployee(int row)
{
	int rowthis = row;
		
	QTableWidgetItem* lastNameitem = tbl->item(row, 1);

	QString lastName = lastNameitem->text();

	Employee2* empEdit = company2.FindEmployeeByLastName2(lastName);

	EditEmployeeDialog widgetEditEmployee(empEdit);

	widgetEditEmployee.resize(100, 100);

	//int res = widgetAddEmployee.exec();
	//long sdf = 789;

	if (QDialog::Rejected == widgetEditEmployee.exec())
		return;

	//	widgetAddEmployee.leName.getText();
	//	Employee2 emp = widgetAddEmployee.getEmploee();

	PrintEmployeeList();

}
void Widget::EditEmployeeCM()
{
	int row = tbl->selectionModel()->currentIndex().row();

	QTableWidgetItem* lastNameitem = tbl->item(row, 1);

	QString lastName = lastNameitem->text();

	Employee2* empEdit = company2.FindEmployeeByLastName2(lastName);

	EditEmployeeDialog widgetEditEmployee(empEdit);

	widgetEditEmployee.resize(100, 100);

	if (QDialog::Rejected == widgetEditEmployee.exec())
		return;

	PrintEmployeeList();
}

void Widget::DelEmployee()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	DeleteEmployeeDialog widgetDeleteEmployee(employees);
	
	widgetDeleteEmployee.resize(100,100);
	
	if (QDialog::Rejected == widgetDeleteEmployee.exec())
		return;

	QString lastName = widgetDeleteEmployee.getLastName();
	
	company2.DeleteEmployee2(lastName);

	PrintEmployeeList();
}

void Widget::DelEmployeeCM()
{
	int row = tbl->selectionModel()->currentIndex().row();

	QTableWidgetItem* lastNameitem = tbl->item(row, 1);

	QString lastName = lastNameitem->text();
	
	company2.DeleteEmployee2(lastName);

	PrintEmployeeList();
}

void Widget::ChangePosition()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	
	ChangePositionDialog widgetChangePositionDialog(employees);
	
	widgetChangePositionDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetChangePositionDialog.exec())
		return;

	QString lastName = widgetChangePositionDialog.getLastName();
	
	Position* pos = widgetChangePositionDialog.getPositionName();
	
	company2.ChangePosition(lastName, pos);
}

void Widget::AssociateEmployee()
{
	std::vector< Employee2* > employees = company2.GetEmployees();
	std::vector< Employee2* > employeesLeaders = company2.getAllEmployeeLeaders();
	
	AssociateAnEmployeeWithAManagerDialog widgetAssociateAnEmployeeWithAManagerDialog(employees, employeesLeaders);
	
	widgetAssociateAnEmployeeWithAManagerDialog.resize(100, 100);
	
	if (QDialog::Rejected == widgetAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	QString lastNameManager = widgetAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	QString lastName = widgetAssociateAnEmployeeWithAManagerDialog.getLastName();
	
	company2.AssociateAnEmployeeWithAManager(lastNameManager, lastName);
}

void Widget::SortLastname()
{
	tbl->sortItems(1);
}

void Widget::SortDate()
{
	tbl->sortItems(5);
}

void Widget::GetListAssociate()
{
	std::vector< Employee2* > employees = company2.getAllEmployeeLeaders();

	GetListAssociateAnEmployeeWithAManagerDialog widgetGetListAssociateAnEmployeeWithAManagerDialog(employees);
	
	widgetGetListAssociateAnEmployeeWithAManagerDialog.resize(100, 110);
	
	if (QDialog::Rejected == widgetGetListAssociateAnEmployeeWithAManagerDialog.exec())
		return;
	
	QString lastNameManager = widgetGetListAssociateAnEmployeeWithAManagerDialog.getLastNameManager();
	
	LeaderBehavior* leader = company2.FindLeaderEmployeeByLastName(lastNameManager);
	if (!leader)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("нет подчинёных!!!"));
		msgBox.exec();

		return;
	}

	{
		QStringList lst;
	
		lst << toQtString("Должность")
			<< QString::fromLocal8Bit("Фамилия")
			<< QString::fromLocal8Bit("Имя")
			<< QString::fromLocal8Bit("Отчество")
			<< QString::fromLocal8Bit("Дата рождения")
			<< QString::fromLocal8Bit("Дата устройство на работу");

		tbl->setHorizontalHeaderLabels(lst);
	}

	auto submissed = leader->getSubmissed();

//	QEmplyeeListDlg dlg(submissed);
//	dlg.exec();

	QDialog submissedDlg;
	
	EmploeesTableWidget* submissedTbl = new EmploeesTableWidget(submissed, &submissedDlg);
	
	QVBoxLayout* layout = new QVBoxLayout();
	
	layout->addWidget(submissedTbl);

	submissedDlg.setLayout(layout);

	submissedDlg.exec();

	return;

	tbl->setColumnCount(6);

	tbl->setRowCount(submissed.size());

	QTableWidgetItem* ptwi = nullptr;

	for (long i = 0; i < submissed.size(); i++)
	{
			//		std::string stdStr = emplyeesVec[i]->GetPositionName();
			//		const char* cStr = stdStr.c_str();
			//
			//		QString qStr = QString::fromLocal8Bit(cStr);

			ptwi = new QTableWidgetItem(submissed[i]->GetPositionName());
			tbl->setItem(i, 0, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetLastName());
			tbl->setItem(i, 1, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetFirstName());
			tbl->setItem(i, 2, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetPatronymic());
			tbl->setItem(i, 3, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetDateOfBirth().toString(Qt::ISODate));
			tbl->setItem(i, 4, ptwi);

			ptwi = new QTableWidgetItem(submissed[i]->GetDateOfHiring().toString(Qt::ISODate));
			tbl->setItem(i, 5, ptwi);
		}
}
void Widget::GetListAssociateCM()
{
	std::vector< Employee2* > employees = company2.GetEmployees();

	int row = tbl->selectionModel()->currentIndex().row();

	QTableWidgetItem *	lastNameitem;

	lastNameitem = tbl->item(row, 1);

	lastNameitem->text();

	QString lastName = lastNameitem->text();

	QString lastNameManager = lastName;

	LeaderBehavior* leader = company2.FindLeaderEmployeeByLastName(lastNameManager);

	if (!leader)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("нет подчинёных!!!"));
		msgBox.exec();
	
		return;
	}

	{
		QStringList lst;

		lst << toQtString("Должность")
			<< QString::fromLocal8Bit("Фамилия")
			<< QString::fromLocal8Bit("Имя")
			<< QString::fromLocal8Bit("Отчество")
			<< QString::fromLocal8Bit("Дата рождения")
			<< QString::fromLocal8Bit("Дата устройство на работу");

		tbl->setHorizontalHeaderLabels(lst);
	}

	auto submissed = leader->getSubmissed();

	//	QEmplyeeListDlg dlg(submissed);
	//	dlg.exec();

	QDialog submissedDlg;

	submissedDlg.resize(800, 800);

	EmploeesTableWidget* submissedTbl = new EmploeesTableWidget(submissed, &submissedDlg);

	QVBoxLayout* layout = new QVBoxLayout();

	layout->addWidget(submissedTbl);

	submissedDlg.setLayout(layout);

	submissedDlg.exec();

	return;
}

void Widget::PrintEmployeeList()
{
	{
		QStringList lst;

		lst << toQtString("Должность")
			<< QString::fromLocal8Bit("Фамилия")
			<< QString::fromLocal8Bit("Имя")
			<< QString::fromLocal8Bit("Отчество")
			<< QString::fromLocal8Bit("Дата рождения")
			<< QString::fromLocal8Bit("Дата устройство на работу");

		tbl->setHorizontalHeaderLabels(lst);
	}

	std::vector< Employee2* > emplyeesVec = company2.GetEmployees();

	tbl->setColumnCount(6);
	
	tbl->setRowCount(emplyeesVec.size());

	QTableWidgetItem* ptwi = nullptr;

	for (int i = 0; i < emplyeesVec.size(); ++i) {
//		QString stdStr = emplyeesVec[i]->GetPositionName();
//		const char* cStr = stdStr.c_str();
//
//		QString qStr = QString::fromLocal8Bit(cStr);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPositionName());
		
		tbl->setItem(i, 0, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetLastName());
		
		tbl->setItem(i, 1, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetFirstName());
		
		tbl->setItem(i, 2, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetPatronymic());
		
		tbl->setItem(i, 3, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfBirth().toString(Qt::ISODate));
		
		tbl->setItem(i, 4, ptwi);

		ptwi = new QTableWidgetItem(emplyeesVec[i]->GetDateOfHiring().toString(Qt::ISODate));
		
		tbl->setItem(i, 5, ptwi);
	}
}

void Widget::getOpenFileName()
{
	QString qstrPath = QFileDialog::getOpenFileName(this, "Open Dialog", "", "");
	
	qstrPath.replace(QRegExp("/"), "\\");
	
	strPath = qstrPath.toStdString();
		
	company2.DeleteEmployeALL();
	
	ftemp.ReadEmplyeesList(company2, strPath);
	
	PrintEmployeeList();
}

void Widget::getSaveFileName()
{
	QString fileNamePath = QFileDialog::getSaveFileName(this,QString::fromUtf8("Сохранить файл"),QDir::currentPath(),";;All files (*.*)");
	
	fileNamePath.replace(QRegExp("/"), "\\");
	
	strPath = fileNamePath.toStdString();
	
	ftemp.WriteEmplyeesList(company2, strPath);
}

void Widget::SaveFile()
{
	ftemp.WriteEmplyeesList(company2, strPath);
}

void Widget::SaveXMLFile()
{

	QString filename = QFileDialog::getSaveFileName(this,
		tr("Save Xml"), ".",
		tr("Xml files (*.xml)"));


	QFile file(filename);
	file.open(QIODevice::WriteOnly);

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement("ONE");

		for (Employee2* emp2 : company2.GetEmployees())
		{
			xmlWriter.writeStartElement("Employee");
			xmlWriter.writeTextElement("PositionName", (emp2->GetPositionName()));
			xmlWriter.writeTextElement("LastName", (emp2->GetLastName()));
			xmlWriter.writeTextElement("FistName", (emp2->GetFirstName()));
			xmlWriter.writeTextElement("Patronymic", (emp2->GetPatronymic()));
			xmlWriter.writeTextElement("DateOfBirth", (emp2->GetDateOfBirth().toString(Qt::ISODate)));
			xmlWriter.writeTextElement("DateOfHiring", (emp2->GetDateOfHiring().toString(Qt::ISODate)));
			
			if (emp2->CanHaveSubmissed())
			{
				if (!emp2->GetLeaderBehavior2()->getSubmissed().empty())
				{

					
					xmlWriter.writeStartElement("open");
					
					std::vector <Employee2*> EmpAssociate = emp2->GetLeaderBehavior2()->getSubmissed();
					for (Employee2* emp2 : EmpAssociate)
					{
						xmlWriter.writeTextElement("PositionName", (emp2->GetPositionName()));
						xmlWriter.writeTextElement("LastName", (emp2->GetLastName()));
						xmlWriter.writeTextElement("FistName", (emp2->GetFirstName()));
						xmlWriter.writeTextElement("Patronymic", (emp2->GetPatronymic()));
						xmlWriter.writeTextElement("DateOfBirth", (emp2->GetDateOfBirth().toString(Qt::ISODate)));
						xmlWriter.writeTextElement("DateOfHiring", (emp2->GetDateOfHiring().toString(Qt::ISODate)));
					}
					//temp2 = "Close Associate An Employee With " + toStdString(emp2->GetLastName()) + "\n";
					xmlWriter.writeEndElement();
				}
			}

			xmlWriter.writeEndElement();
		}
	xmlWriter.writeEndElement();



	file.close();
}
void Widget::ReadXMLFile()
{
	company2.DeleteEmployeALL();

	QXmlStreamReader Rxml;

	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Xml"), ".",
		tr("Xml files (*.xml)"));

	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		std::cerr << "Error: Cannot read file " << qPrintable(filename)
			<< ": " << qPrintable(file.errorString())
			<< std::endl;

	}

	Rxml.setDevice(&file);
	Rxml.readNext();
	QString PositionName;
	std::string pos;
	QString LastName;
	QString FistName;
	QString nameLider;
	QString Patronymic;
	QDate DateOfBirth;
	QDate DateOfHiring;




	while (!Rxml.atEnd())
	{
		if (Rxml.isStartElement())
		{
			if (Rxml.name() == "ONE")
			{
				Rxml.readNext();
			}
			else if (Rxml.name() == "Employee")
			{
				Rxml.readNext();
				while (!Rxml.atEnd())
				{
					if (Rxml.isEndElement())
					{
						Rxml.readNext();
						break;
					}

					else if (Rxml.isStartElement())
					{
						if (Rxml.name() == "PositionName")
						{
							PositionName = Rxml.readElementText();
							pos = toStdString(PositionName);
							Rxml.readNext();
							Rxml.readNext();
							if (Rxml.name() == "LastName")
							{
								LastName = Rxml.readElementText();
								Rxml.readNext();
								Rxml.readNext();
								if (Rxml.name() == "FistName")
								{
									FistName = Rxml.readElementText();
									Rxml.readNext();
									Rxml.readNext();
									if (Rxml.name() == "Patronymic")
									{
										Patronymic = Rxml.readElementText();
										Rxml.readNext();
										Rxml.readNext();
										if (Rxml.name() == "DateOfBirth")
										{
											DateOfBirth = QDate::fromString((Rxml.readElementText()), Qt::ISODate);
											Rxml.readNext();
											Rxml.readNext();
											if (Rxml.name() == "DateOfHiring")
											{
												DateOfHiring = QDate::fromString((Rxml.readElementText()), Qt::ISODate);
												tempFromFile(LastName, pos, FistName, Patronymic, DateOfBirth, DateOfHiring);
												Rxml.readNext();
												Rxml.readNext();
												QStringRef tem = Rxml.text();
												if (Rxml.name() == "open")
												{
													nameLider = LastName;
													Rxml.readNext();
													while (!Rxml.atEnd())
													{
														if (Rxml.isEndElement())
														{
															Rxml.readNext();
															break;
														}

														else if (Rxml.isStartElement())
														{
															if (Rxml.name() == "PositionName")
															{
																PositionName = Rxml.readElementText();
																pos = toStdString(PositionName);
																Rxml.readNext();
																Rxml.readNext();
																if (Rxml.name() == "LastName")
																{
																	LastName = Rxml.readElementText();
																	Rxml.readNext();
																	Rxml.readNext();
																	if (Rxml.name() == "FistName")
																	{
																		FistName = Rxml.readElementText();
																		Rxml.readNext();
																		Rxml.readNext();
																		if (Rxml.name() == "Patronymic")
																		{
																			Patronymic = Rxml.readElementText();
																			Rxml.readNext();
																			Rxml.readNext();
																			if (Rxml.name() == "DateOfBirth")
																			{
																				DateOfBirth = QDate::fromString((Rxml.readElementText()), Qt::ISODate);
																				Rxml.readNext();
																				Rxml.readNext();
																				if (Rxml.name() == "DateOfHiring")
																				{
																					DateOfHiring = QDate::fromString((Rxml.readElementText()), Qt::ISODate);
																					tempFromFile(LastName, pos, FistName, Patronymic, DateOfBirth, DateOfHiring);
																					company2.AssociateAnEmployeeWithAManager(nameLider, LastName);
																					Rxml.readNext();
																					Rxml.readNext();

																				}
																			}
																		}
																	}
																}
															}



														}
														else
														{
															Rxml.readNext();
														}
													}
												}
											}
										}
									}
								}
							}
						}//Rxml.readNext();



					}
					else
					{
						Rxml.readNext();
					}
				}
			}
			else
				{
				Rxml.readNext();
				}
		}
		else
		{
			Rxml.readNext();
		}
	}
		file.close();

		if (Rxml.hasError())
		{
			std::cerr << "Error: Failed to parse file "
				<< qPrintable(filename) << ": "
				<< qPrintable(Rxml.errorString()) << std::endl;
		}
		else if (file.error() != QFile::NoError)
		{
			std::cerr << "Error: Cannot read file " << qPrintable(filename)
				<< ": " << qPrintable(file.errorString())
				<< std::endl;
		}
	
}

//void Widget::SaveSqlFile()
//{
//	QString filename = QFileDialog::getSaveFileName(this,
//		tr("Save Sql"), ".",
//		tr("Sql files (*.sql)"));
//
//
//	QFile file(filename);
//	file.open(QIODevice::WriteOnly);
//
//
//
//}
//void Widget::ReadSqlFile()
//{
//
//}

void Widget::tempFromFile(const QString& lastName, std::string ch, const QString& firstName, QString patronymic, const QDate& dateOfBirth, const QDate& dateOfHiring)
{
	Position* pos = nullptr;

	if ("Рабочий" == ch)
	{
		pos = new WorkerPosition();
	}
	else if ("Менеджер" == ch)
	{
		pos = new ManagerPosition();
	}
	else if ("Директор" == ch)
	{
		pos = new DirectorPosition();
	}
	else if ("Уборщик" == ch)
	{
		pos = new CleanerPosition();
	}
	else
	{
		//std::cout << "Попробуйте mmmmmmmmmmmmmmеще\n";

	}

	if (!pos)
	{

		//std::cout << "pos = nullptr\n";
		pos = nullptr;
		//break;

	}

	if (pos != nullptr)
	{
		company2.AddEmployeeFromFile(new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring));

	}
}

void Widget::ExitList()
{	
	ftemp.WriteEmplyeesList(company2, strPath);
	
	QApplication::quit();
}
