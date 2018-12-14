//// listfirm.cpp: определяет точку входа для консольного приложения.
////
////Создать список персонала фирмы.
////В фирме все работники делятся на следующие типы :
////1) Работник:
////-ФИО
////- Дата рождения
////- Дата принятия на работу
////2) Менеджер
////- ФИО
////- Дата рождения
////- Дата принятия на работу
////- Список работников в подчинении данного менеджера
////3) Другие(руководство, секретари и т.д.)
////- ФИО
////- Дата рождения
////- Дата принятия на работу
////- Текстовое описание сотрудника
////Список сотрудников должен позволять добавлять, удалять, изменять тип сотрудника, привязывать сотрудника к менеджеру, сортировать список по фамилиям, датам принятия на работу.Данные необходимо читать и писать в файл.
////Требования к программной реализации :
////-Приложение должно быть консольным
////- Входные данные(при добавлении сотрудника) должны читаться из текстового файла
//
//#include "stdafx.h"
//
//#include "Employee.h"
//#include "File.h"
//#include "Company.h"
//#include "Position.h"
//
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include "utils.h"
//
//#define CM_ADD_EMPLOYEE  '1'
//#define CM_DEL_EMPLOYEE  '2'
//#define CM_CHANGE_POSITION  '3'
//#define CM_ASSOCIATE_EMPLOYEE  '4'
//#define CM_SORT_LASTNAME  '5'
//#define CM_SORT_DATE  '6'
//#define CM_EXIT  '7'
//#define CM_PRINT_EMPLYEES_LIST  '8'
//#define CM_GET_LIST_ASSOCIATE  '9'
//
//int firmAppMain(int argc, _TCHAR* argv[])
//{
//	Company2 company2;
//	/*Employee2* emp2 = new Employee2("Иванов", new WorkerPosition(), "Иван", "Иванович", "1985.05.12", "2000.05.08");
//	  company2.AddEmployee(emp2);
//	  Employee2* emp22 = new Employee2("Петров", new ManagerPosition(), "Иван", "Николаевич", "1965.01.12", "2010.02.22");
//	  company2.AddEmployee(emp22);
//	  Employee2* emp23 = new Employee2("Соколова", new WorkerPosition(), "Светлана", "Сергеевна", "1985.07.19", "2005.01.06");
//	  company2.AddEmployee(emp23);
//	  Employee2* emp24 = new Employee2("Бобров", new ManagerPosition(), "Иван", "Иванович", "1956.02.13", "2012.06.08");
//	  company2.AddEmployee(emp24);
//	  Employee2* emp25 = new Employee2("Сидозвогр", new WorkerPosition(), "Николай", "Петрович", "1933.09.17", "2016.03.04");
//	  company2.AddEmployee(emp25);
//	  Employee2* emp26 = new Employee2("Сиськина", new DirectorPosition(), "Нина", "Олеговна", "1997.05.16", "2016.04.08");
//	  company2.AddEmployee(emp26);
//	  Employee2* emp27 = new Employee2("Торопышка", new WorkerPosition(), "Наталья", "Ивановна", "1995.11.06", "2011.10.03");
//	  company2.AddEmployee(emp27);
//	  Employee2* emp28 = new Employee2("Буржин", new WorkerPosition(), "Петр", "Кованович", "1991.11.11", "2013.11.13");
//	  company2.AddEmployee(emp28);*/
////	ComponyConsole consoleWrapper;
//
//	File2 ftemp;
//	
//	ftemp.ReadEmplyeesList(company2);
//
//
//	char ch;
//	do
//	{
//		std::cout << "Выберите действие: ... " << std::endl;
//		std::cout << " 1 - добавить сотрудника" << std::endl;
//		std::cout << " 2 - удалить сотрудника" << std::endl;
//		std::cout << " 3 - изменить тип сотрудника" << std::endl;
//		std::cout << " 4 - привязывать сотрудника к менеджеру" << std::endl;
//		std::cout << " 5 - сортировать список по фамилиям" << std::endl;
//		std::cout << " 6 - сортировать датам принятия на работу" << std::endl;
//		std::cout << " 8 - вывести список работников" << std::endl;
//		std::cout << " 9 - вывести список работников привязаных к менеджеру" << std::endl;
//		std::cout << " 7 - Выход" << std::endl;
//		std::cin >> ch;
//		switch (ch)
//		{
//		case CM_ADD_EMPLOYEE:
//					{
//					bool askAgain = true;
//					while (askAgain)
//						{
//						Employee2* emp = consoleWrapper.MakeEmployeFromStdin(askAgain);
//						if (!emp)
//						continue;
//
//						company2.AddEmployee(emp);
//						}
//					}
//			break;
//
//		case CM_DEL_EMPLOYEE:
//					{
//					QString lastName = toQtString( consoleWrapper.AscEmployeLast() );
//										
//					company2.DeleteEmployee2(lastName);
//					}
//			break;
//
//		case CM_CHANGE_POSITION:
//					{
//					QString lastName = toQtString( consoleWrapper.AscEmployeLast() );
//					
//					Position* pos = consoleWrapper.AscPosition();
//
//					company2.ChangePosition(lastName, pos);
//					}
//			break;
//
//		case CM_ASSOCIATE_EMPLOYEE:
//					{
//					QString lastNameManager = toQtString( consoleWrapper.AscManagerLast() );
//
//					QString lastName = toQtString( consoleWrapper.AscEmployeLast() );
//
//					company2.AssociateAnEmployeeWithAManager(lastNameManager, lastName);
//					}
//			break; 
//
//		case CM_SORT_LASTNAME:
//					company2.SortTheListByLastName(); 
//					break;
//
//		case CM_SORT_DATE: 
//			company2.SortTheListByDateOfHiring(); 
//			break;
//
//		case CM_PRINT_EMPLYEES_LIST:
//					ComponyConsole().PrintEmplyeesList(company2); 
//					break;
//
//		case CM_GET_LIST_ASSOCIATE:
//					{
//					QString lastName = toQtString( consoleWrapper.AscManagerLast() );
//					company2.GetListAssociateAnEmployeeWithAManager(lastName);
//					}
//			break;
//
//		case CM_EXIT:
//			ftemp.WriteEmplyeesList(company2);
//					std::cout << "Выход...\n";
//			break;
//
//		default:	std::cout << "Попробуйте еще\n";
//			break;
//		}
//
//
//	} while (ch != '7');
//
//
//	return 0;
//
//}
//
////void testTwEmplyeeWithTheSameName()
////{
////  Company2 company;
////
////  File2 ftemp;
////
////  Employee2* emp2 = new Employee2("m", new ManagerPosition(), "mashaf", "mashap", "1900.05.78", "1900.05.78");
////  company.AddEmployee(emp2);
////
////  Employee2* emp1 = new Employee2("m", new ManagerPosition(), "mashaf", "mashap", "1900.05.78", "1900.05.78");
////  company.AddEmployee(emp1);
////  
////  //company.AddEmployee( leader );
////  //company.AddEmployee( leader );
////  ftemp.WriteEmplyeesList(company);
////  if (company.GetEmployeesCount() != 1)
////	  std::cout << "error" << std::endl;
////}
////
////void testRemoveEmploye1()
////{
////  Company2 company;
////  Employee2* emp3 = new Employee2("a", new CleanerPosition(), "alexander", "alexander", "1900.45.78", "1900.45.78");
////  Employee2* emp4 = new Employee2("m", new ManagerPosition(), "mashaf", "mashap", "1900.05.78", "1900.05.78");
////  company.AddEmployee(emp3);
////  company.AddEmployee(emp4);
////
////  company.AssociateAnEmployeeWithAManager("m","a" );
////
////  company.DeleteEmployee("alexander");
////
//// // if (emp4->GetLeaderBehavior().empty())
////	  std::cout << "error2" << std::endl;
////}
////
////void testRemoveEmploye2()
////{
////  Company2 company;
////  Employee2* emp5 = new Employee2("a2", new CleanerPosition(), "alexander", "alexander", "1900.75.78", "1900.75.78");
////  	company.AddEmployee(emp5);
////  
////  	Employee2* emp6 = new Employee2("333m2", new ManagerPosition(), "mashaf", "mashap", "1900.45.11", "1900.45.11");
////  	company.AddEmployee(emp6);
////  
////  	Employee2* emp8 = new Employee2("m222", new ManagerPosition(), "mashaf", "mashap", "1900.45.11", "1900.45.11");
////  	company.AddEmployee(emp8);
////  
////  	Employee2* emp7 = new Employee2("d2", new WorkerPosition(), "dashaf", "dashap", "1900.45.00", "1900.45.00");
////  	company.AddEmployee(emp7);
////  /*company.AddEmployee( leader );
////  company.AddEmployee( manager );
////  company.AddEmployee( worker );*/
////
////	emp6->GetLeaderBehavior2()->addSubmissed(emp8);
////	emp8->GetLeaderBehavior2()->addSubmissed(emp7);
////
////  company.DeleteEmployee2( "m222" );
////
//// // if (emp6->GetLeaderBehavior().empty())
////	  std::cout << "error3" << std::endl;
////
////  if (company.GetEmployeesCount() != 3)
////	  std::cout << "error4" << std::endl;
////}
////
////void testChangeType()
////{
////	Company2 company;
////	Employee2* emp5 = new Employee2("a2", new CleanerPosition(), "alexander", "alexander", "1900.75.78", "1900.75.78");
////	company.AddEmployee(emp5);
////	emp5->SetPositionName(new DirectorPosition());
////	
////	if (emp5->GetPositionName() == "Уборщик")
////	{
////		std::cout << "error4 Уборщик" << std::endl;
////	}std::cout << emp5->GetPositionName() << std::endl;
////}
////
////void runAllTests()
////{
////	testTwEmplyeeWithTheSameName();
////  testRemoveEmploye1();
////  testRemoveEmploye2();
////}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "");
//
//	  /*runAllTests();
//	  return 0;*/
//
//	return firmAppMain(argc, argv);
//}
//
