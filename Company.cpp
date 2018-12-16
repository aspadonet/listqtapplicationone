#include "stdafx.h"
#include "Company.h"
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "utils.h"

void Company2::AddEmployee(Employee2* empl)
{
	if (EmployeeMatchCheck(empl))
	{
		employees.push_back(empl);
	}
	else
	{
		std::cout << "Такой работник уже есть" << std::endl;
	}
	//employees.push_back(empl);
}

void Company2::AddEmployeeFromFile(Employee2* empl)
{
	if (EmployeeMatchCheck(empl))
	{
		employees.push_back(empl);
	}
	
}


void Company2::DeleteEmployee(QString lastName)
{
	
	std::vector<Employee2*>::const_iterator it = FindEmployeeByLastName(lastName);
	auto itEmplForDelete = it;

	if (itEmplForDelete == employees.cend())
	{
		std::cout << "Сотрудник с введенной фамилией не найден" << std::endl;
		
	}
	else{

		employees.erase(it);

	}
}

void Company2::DeleteEmployee2(QString lastName )
{
	std::vector<Employee2*>::const_iterator it = FindEmployeeByLastName(lastName);

  if( it == employees.cend() )
  {
    std::cout << "Сотрудник с введенной фамилией не найден" << std::endl;
    return;
  }

  Employee2* emp = *it;

  DeleteEmployeFromLeaders(emp);

  employees.erase( it );
  delete emp;
}

void Company2::DeleteEmployeFromLeaders(Employee2* emp)
{
  std::vector< LeaderBehavior* > leaders = getAllLeaders();
  for( auto leader : leaders )
  {
	  leader->DeleteSubmissed(emp);
  }
}
void Company2::DeleteEmployeALL()
{
	employees.clear();
}

void Company2::ChangePosition(QString lastName, Position* pos)
{
  Employee2* emp = FindEmployeeByLastName2( lastName );
  if( !emp )
  {
	  std::cout << "Сотрудник с введенной фамилией не найден" << std::endl;
	  return;
  }

	emp->SetPositionName(pos);
}

void Company2::AssociateAnEmployeeWithAManager(QString lastNameManager, QString lastName )
{
  LeaderBehavior* leader = FindLeaderEmployeeByLastName( lastNameManager );
  if( !leader )
  {
	  std::cout << "Сотрудник с введенной фамилией не найден1" << std::endl;
	  return;
  }

	Employee2* emp = FindEmployeeByLastName2( lastName );
  if( !emp )
  {
	  std::cout << "Сотрудник с введенной фамилией не найден2" << std::endl;
	  return;
  }

  leader->addSubmissed( emp );

//	Manager->SetLeaderBehavior(emp);
}

void Company2::GetListAssociateAnEmployeeWithAManager(QString lastNameManager)
{
  LeaderBehavior* leader = FindLeaderEmployeeByLastName( lastNameManager );
  if( !leader )
  {
	  std::cout << "Сотрудник с введенной фамилией не найден" << std::endl;
	  return;
  }
	
//	ComponyConsole().PrintSubmissedList( leader );//	ComponyConsole().PrintSubmissedList( leader );
}

std::vector< Employee2*> Company2::GetEmployees()
{
	return employees;
}

void Company2::SortTheListByLastName()
{
	std::set <QString> setEmployoee;

	for (long i = 0; i < employees.size(); i++)
	{
		Employee2* emp = employees[i];
		QString lastName = emp->GetLastName();

		setEmployoee.insert(lastName);
	}

	std::vector<Employee2*> employeesLastName;

	for (auto LastName : setEmployoee)
	{
		std::vector<Employee2*>::const_iterator itLastName = FindEmployeeByLastName(LastName);

		Employee2* LN = *itLastName;

		employeesLastName.push_back(LN);
				
	}
//	ComponyConsole().PrintEmplyeesListBySortLastName(employeesLastName);//	ComponyConsole().PrintEmplyeesListBySortLastName(employeesLastName);
}

void Company2::SortTheListByDateOfHiring()
{
	std::set <QDate> setEmployoee;

	for (long i = 0; i < employees.size(); i++)
	{
		Employee2* emp = employees[i];
	QDate DateOfHiring = emp->GetDateOfHiring();

		setEmployoee.insert(DateOfHiring);
	}

	std::vector<Employee2*> employeesDateOfHiring;

	for (auto DateOfHiring : setEmployoee)
	{
		std::vector<Employee2*>::const_iterator itDateOfHiring = FindEmployeeByDateOfHiring(DateOfHiring);

		Employee2* LN = *itDateOfHiring;

		employeesDateOfHiring.push_back(LN);

	}
//	ComponyConsole().PrintEmplyeesListBySortLastName(employeesDateOfHiring);//	ComponyConsole().PrintEmplyeesListBySortLastName(employeesDateOfHiring);
	
}

std::vector<Employee2*>::const_iterator Company2::FindEmployeeByLastName(const QString& lastName)
{
	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* empl = *it;
		if (empl->GetLastName() == lastName)
		{
			return it;
			//break;

		}
		
	}
	auto it = employees.cend();
	return  it;
}

std::vector<Employee2*>::const_iterator Company2::FindEmployeeByDateOfHiring(const QDate& DateOfHiring)
{
	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* empl = *it;
		if (empl->GetDateOfHiring() == DateOfHiring)
		{
			return it;
			//break;

		}

	}
	auto it = employees.cend();
	return  it;
}
//void Company2::setAllLeaders()
//{
//	for (auto it = employees.cbegin(); it != employees.cend(); it++)
//	{
//		Employee2* empl = *it;
//		if (empl->CanHaveSubmissed())
//		{
//			leaders.push_back(empl->GetLeaderBehavior2());
//			//break;
//
//		}
//
//	}
//
//}

std::vector< LeaderBehavior* >  Company2::getAllLeaders()

{
	//setAllLeaders();
	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* empl = *it;
		if (empl->CanHaveSubmissed())
		{
			leaders.push_back(empl->GetLeaderBehavior2());
			//break;

		}

	}
	return leaders;
}

std::vector< Employee2* >  Company2::getAllEmployeeLeaders()
{
	//setAllLeaders();
	std::vector< Employee2* > employeesleaders;

	for (auto it = employees.cbegin(); it != employees.cend(); it++)
	{
		Employee2* empl = *it;
		if (empl->CanHaveSubmissed())
		{
			employeesleaders.push_back(empl);
			//break;

		}

	}
	return employeesleaders;
}

Employee2* Company2::FindEmployeeByLastName2( const QString& lastName )
{
  auto it = FindEmployeeByLastName( lastName );
  if( it == employees.cend() )
    return nullptr;

  return *it;
}

LeaderBehavior* Company2::FindLeaderEmployeeByLastName( const QString& lastName )
{
  for( auto it = employees.cbegin(); it != employees.cend(); it++ )
  {
    Employee2* empl = *it;
    if( empl->CanHaveSubmissed() && empl->GetLastName() == lastName )
    {
      return empl->GetLeaderBehavior2();
      //break;

    }

  }

  return nullptr;
}

bool Company2::EmployeeMatchCheck(Employee2* empl)
{
	if (employees.size() != 0){
		for (auto it = employees.cbegin(); it != employees.cend(); it++)
		{
			Employee2* emplnew = *it;
			if (empl->GetLastName() == emplnew->GetLastName()
				&& empl->GetFirstName() == emplnew->GetFirstName()
				&& empl->GetPatronymic() == emplnew->GetPatronymic()
				&& empl->GetDateOfBirth() == emplnew->GetDateOfBirth()
				)
			{
				return 0;
			}
		}
	}
		return 1;
	
}
//PrintReportRow("Должность", "Фамилия", "Имя", "Отчество", "Дата рождения", "Дата устройство на работу", "Описание");

//void ComponyConsole::PrintEmplyeesList(Company2& company)
//{
//	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
//
//	PrintReportRow("Должность", "Фамилия", "Имя", "Отчество", "Дата", "Дата");
//
//	for (Employee2* emp2 : company.GetEmployees())
//	{
//		PrintReportRow(emp2->GetPositionName(), emp2->GetLastName(), emp2->GetFirstName(), emp2->GetPatronymic(), emp2->GetDateOfBirth(), emp2->GetDateOfHiring());
//	}
//}

int Company2::GetEmployeesCount()
{
	return employees.size();
}
////void ComponyConsole::PrintLeaderBehavior(std::vector<Employee2*>  Employee)
////{
////	std::cout << "список  сотрудников привязыных к менеджеру" << std::endl;
////	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
////	std::cout << std::endl;
////
////	PrintReportRow("Должность", "Фамилия", "Имя", "Отчество", 000, 000);
////
////	for (long i = 0; i < Employee.size(); i++)
////	{
////		Employee2* emp2 = Employee[i];
////		PrintReportRow(emp2->GetPositionName(), emp2->GetLastName(), emp2->GetFirstName(), emp2->GetPatronymic(), emp2->GetDateOfBirth(), emp2->GetDateOfHiring());
////	}
////	
////}
//
//void ComponyConsole::PrintSubmissedList( LeaderBehavior* leader )
//{
//  std::cout << "список  сотрудников привязыных к менеджеру" << std::endl;
//  std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
//  std::cout << std::endl;
//
//  PrintReportRow("Должность", "Фамилия", "Имя", "Отчество", "Дата", "Дата");
//
//  auto submissed = leader->getSubmissed();
//  for( long i = 0; i < submissed.size(); i++ )
//  {
//    Employee2* emp2 = submissed[ i ];
//    PrintReportRow( emp2->GetPositionName(), emp2->GetLastName(), emp2->GetFirstName(), emp2->GetPatronymic(), emp2->GetDateOfBirth(), emp2->GetDateOfHiring() );
//  }
//}
//
//void ComponyConsole::PrintEmplyeesListBySortLastName(std::vector<Employee2*>  employeesLastName)
//{
//	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
//
//	PrintReportRow("Должность", "Фамилия", "Имя", "Отчество", "Дата", "Дата");
//
//	for (Employee2* emp2 : employeesLastName)
//	{
//		PrintReportRow(emp2->GetPositionName(), emp2->GetLastName(), emp2->GetFirstName(), emp2->GetPatronymic(), emp2->GetDateOfBirth(), emp2->GetDateOfHiring());
//	}
//}
//
//void ComponyConsole::PrintReportRow(const std::string& pos, const std::string& lastName, const std::string& firstName, const std::string& patronymic, const std::string& dateOfBirth, const std::string& dateOfHiring)
//{ 
//	std::cout << std::left
//		<< std::setw(15) << pos
//		<< std::setw(15) << lastName.toLocal8Bit().constData()
//		<< std::setw(15) << firstName
//		<< std::setw(15) << patronymic
//		<< std::setw(15) << dateOfBirth
//		<< std::setw(30) << dateOfHiring
//		<< std::setw(30) << "" << std::endl;
//}
//
//std::string ComponyConsole::AscEmployeLast()
//{
//	
//		std::string LastName;
//		std::cout << " Фамилия сотрудника" << std::endl;
//		std::cin >> LastName;
//		
//		return LastName;
//
//}
//std::string ComponyConsole::AscManagerLast()
//{
//
//	std::string LastName;
//	std::cout << " Фамилия Менеджера" << std::endl;
//	std::cin >> LastName;
//
//	return LastName;
//
//}
//
//Position* ComponyConsole::AscPosition()
//{
//	
//	std::cout << "Выберите действие: ... " << std::endl;
//	std::cout << " 1 - добавить рабочего" << std::endl;
//	std::cout << " 2 - добавить менеджера" << std::endl;
//	std::cout << " 3 - добавить руководителя" << std::endl;
//	std::cout << " 4 - добавить уборщика" << std::endl;
//	std::cout << " 7 - Выход" << std::endl;
//
//	char ch;
//	std::cin >> ch;
//
//	Position* pos = nullptr;
//	switch (ch)
//	{
//	case '1':
//		pos = new WorkerPosition();
//		break;
//	case '2':
//		pos = new ManagerPosition();
//		break;
//	case '3':
//		pos = new DirectorPosition();
//		break;
//	case '4':
//		pos = new CleanerPosition();
//		break;
//	case '7': std::cout << "Выход...\n";
//		return nullptr;
//
//	default: std::cout << "Попробуйте еще\n";
//		return nullptr;
//	}
//
//	if (!pos)
//	{
//		// _DEBUG_ERROR( "" );
//		return nullptr;
//	}
//
//
//
//	return pos;
//}
//
//Employee2* ComponyConsole::MakeEmployeFromStdin(bool& askAgain)
//{
//	askAgain = true;
//
//	std::cout << "Выберите действие: ... " << std::endl;
//	std::cout << " 1 - добавить рабочего" << std::endl;
//	std::cout << " 2 - добавить менеджера" << std::endl;
//	std::cout << " 3 - добавить руководителя" << std::endl;
//	std::cout << " 4 - добавить уборщика" << std::endl;
//	std::cout << " 7 - Выход" << std::endl;
//
//	char ch;
//	std::cin >> ch;
//
//	Position* pos = nullptr;
//	switch (ch)
//	{
//	case '1':
//		pos = new WorkerPosition();
//		break;
//	case '2':
//		pos = new ManagerPosition();
//		break;
//	case '3':
//		pos = new DirectorPosition();
//		break;
//	case '4':
//		pos = new CleanerPosition();
//		break;
//	case '7': std::cout << "Выход...\n";
//		askAgain = false;
//		return nullptr;
//
//	default: std::cout << "Попробуйте еще\n";
//		return nullptr;
//	}
//
//	if (!pos)
//	{
//		// _DEBUG_ERROR( "" );
//		return nullptr;
//	}
//
//	
//	std::string stdStrLastName;
//
//	std::cout << " Фамилия " << std::endl;
//	std::cin >> stdStrLastName;
//
//	QString lastName = toQtString(  stdStrLastName );
//
//
//	std::string firstName;
//
//	std::cout << " Имя " << std::endl;
//	std::cin >> firstName;
//
//	std::string patronymic;
//
//	std::cout << " Очество " << std::endl;
//	std::cin >> patronymic;
//
//	std::string dateOfBirth;
//	std::string dateOfYear;
//	std::string dateOfMonth;
//	std::string dateOfDay;
//	std::cout << " Дата рождения " << std::endl;
//	std::cout << " Год " << std::endl;
//	std::cin >> dateOfYear;
//	std::cout << " Месяц " << std::endl;
//	std::cin >> dateOfMonth;
//	std::cout << " День " << std::endl;
//	std::cin >> dateOfDay;
//	dateOfBirth = dateOfYear + "." + dateOfMonth + "." + dateOfDay;
//	std::string dateOfHiring;
//
//	std::cout << " Дата принятия на работу " << std::endl;
//	std::cout << " Год " << std::endl;
//	std::cin >> dateOfYear;
//	std::cout << " Месяц " << std::endl;
//	std::cin >> dateOfMonth;
//	std::cout << " День " << std::endl;
//	std::cin >> dateOfDay;
//	dateOfHiring = dateOfYear + "." + dateOfMonth + "." + dateOfDay;;
//
//
//	return new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring);
//}

void File2::ReadEmplyeesList(Company2& company, std::string strpath)
{
	std::string path = strpath;
	std::ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		std::cout << "NOT open file" << std::endl;
	}
	else
	{
		std::string str;
		while (!fin.eof())
		{
			str = "";
			getline(fin,str);
						
			if (str != "")
			{

				std::string word;

				std::istringstream iss(str, std::istringstream::in);
				std::vector<std::string> wordsVector;
				while (iss >> word)
				{
					wordsVector.push_back(word);
				}
			
				std::string ch;
				ch = wordsVector[0];

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

				QString lastName = toQtString( wordsVector[1] );

				QString firstName = toQtString( wordsVector[2] );

				QString patronymic = toQtString( wordsVector[3] );

				QDate dateOfBirth = QDate::fromString(toQtString(wordsVector[4]), Qt::ISODate);

				QDate dateOfHiring = QDate::fromString(toQtString(wordsVector[5]), Qt::ISODate);


				if (pos != nullptr)
				{
					company.AddEmployeeFromFile(new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring));
					//company.GetEmployees().push_back(new Employee2(lastName, pos, firstName, patronymic, dateOfBirth, dateOfHiring));
				}
				
			}
		}
	}
	fin.close();

	fin.open(path);
	if (!fin.is_open())
	{
		std::cout << "NOT open file" << std::endl;
	}
	else
	{
		std::string str;
		while (!fin.eof())
		{
			str = "";
			getline(fin, str);
			


			if (str != "")
			{

				std::string word;

				std::istringstream iss(str, std::istringstream::in);
				std::vector<std::string> wordsVector;
				while (iss >> word)
				{
					wordsVector.push_back(word);
				}

				
				if (wordsVector[0] == "open")
				{

					QString nameLider = toQtString( wordsVector[5] );
					std::string swV = "";
					while (swV != "Close")
					{

						str = "";
						getline(fin, str);
						
						std::string word2;

						std::istringstream iss(str, std::istringstream::in);
						std::vector<std::string> wordsVector2;
						while (iss >> word)
						{
							wordsVector2.push_back(word);
						}
						

						QString lastName = toQtString( wordsVector2[1] );
						if (wordsVector2[0] == "Close")
						{
							swV = "Close";
							
						}
						else
						{

							company.AssociateAnEmployeeWithAManager(nameLider, lastName);
						}
					
					}
					
					
				}

				
			}
		}
	}
	fin.close();

}
void File2::WriteEmplyeesList(Company2& company, std::string strpath)
{
	std::string path = strpath;
	std::ofstream fout;
	fout.open(path);// , std::ofstream::app);
	if (!fout.is_open())
	{
		std::cout << "NOT open file" << std::endl;
	}
	else
	{
		for (Employee2* emp2 : company.GetEmployees())
		{
			std::string temp = "";
			
			temp = toStdString( emp2->GetPositionName() ) + " " + toStdString( emp2->GetLastName() ) + " " + toStdString( emp2->GetFirstName() )+ " " + toStdString( emp2->GetPatronymic() ) + " " + toStdString(emp2->GetDateOfBirth().toString(Qt::ISODate)) + " " + toStdString(emp2->GetDateOfHiring().toString(Qt::ISODate)) + "\n";
			
			fout << temp;
			if (emp2->CanHaveSubmissed())
			{
				if (!emp2->GetLeaderBehavior2()->getSubmissed().empty())
				{

					std::string temp2 = "open Associate An Employee With " + toStdString( emp2->GetLastName() ) + "\n";

					fout << temp2;
					std::vector <Employee2*> EmpAssociate = emp2->GetLeaderBehavior2()->getSubmissed();
					for (Employee2* emp2 : EmpAssociate)
					{
						std::string temp3 = "";

						temp3 = toStdString(emp2->GetPositionName()) + " " + toStdString(emp2->GetLastName()) + " " + toStdString(emp2->GetFirstName()) + " " + toStdString(emp2->GetPatronymic()) + " " + toStdString(emp2->GetDateOfBirth().toString(Qt::ISODate)) + " " + toStdString(emp2->GetDateOfHiring().toString(Qt::ISODate)) + "\n";

						fout << temp3;
					}
					temp2 = "Close Associate An Employee With " + toStdString( emp2->GetLastName() ) + "\n";
					fout << temp2;
				}
			}
		}

	}
	fout.close();
}