#pragma once

#include <vector>
#include "Employee.h"
#include <set>

class Company2
{
private:
	std::vector< Employee2* > employees;
	std::vector< LeaderBehavior* > leaders;

public:
	void AddEmployee(Employee2* empl);
	void AddEmployeeFromFile(Employee2* empl);
	std::vector< Employee2* > GetEmployees();
	// std::vector< Employee2* > GetLeaderEmployees();
	void DeleteEmployee(QString lastName);
	void DeleteEmployee2(QString lastName);
	void DeleteEmployeFromLeaders(Employee2* empl);
	void ChangePosition(QString lastName, Position* pos);
	void AssociateAnEmployeeWithAManager(QString lastNameManager, QString lastName);
	void GetListAssociateAnEmployeeWithAManager(QString lastNameManager);
	void SortTheListByLastName();
	void SortTheListByDateOfHiring();
	bool EmployeeMatchCheck(Employee2* empl);
	//void setAllLeaders();
	std::vector<Employee2*>::const_iterator FindEmployeeByLastName(const QString& lastName);
	std::vector<Employee2*>::const_iterator FindEmployeeByDateOfHiring(const std::string& DateOfHiring);
	std::vector< LeaderBehavior* >  getAllLeaders();

  Employee2* FindEmployeeByLastName2( const QString& lastName );
  LeaderBehavior* FindLeaderEmployeeByLastName( const QString& lastName );

  int GetEmployeesCount();

	
};

class ComponyConsole
{
public:
	void PrintEmplyeesList(Company2& company);
//	void PrintLeaderBehavior(std::vector<Employee2*>  Employee2);
   void PrintSubmissedList(LeaderBehavior* leader );

	void PrintEmplyeesListBySortLastName(std::vector<Employee2*>  Employee2);
	void PrintReportRow(const std::string& pos, const QString& lastName, const std::string& firstName, const std::string& patronymic, const std::string& dateOfBirth, const std::string& dateOfHiring);
	std::string AscEmployeLast();
	std::string AscManagerLast();
	Position* ComponyConsole::AscPosition();
	Employee2* MakeEmployeFromStdin(bool& askAgain);
};

class File2
{

public:
	void  ReadEmplyeesList(Company2& company);
	void  WriteEmplyeesList(Company2& company);

};
