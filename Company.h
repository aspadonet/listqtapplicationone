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
	void DeleteEmployee(std::string lastName);
	void DeleteEmployee2(std::string lastName);
	void DeleteEmployeFromLeaders(Employee2* empl);
	void ChangePosition(std::string lastName, Position* pos);
	void AssociateAnEmployeeWithAManager(std::string lastNameManager, std::string lastName);
	void GetListAssociateAnEmployeeWithAManager(std::string lastNameManager);
	void SortTheListByLastName();
	void SortTheListByDateOfHiring();
	bool EmployeeMatchCheck(Employee2* empl);
	//void setAllLeaders();
	std::vector<Employee2*>::const_iterator FindEmployeeByLastName(const std::string& lastName);
	std::vector<Employee2*>::const_iterator FindEmployeeByDateOfHiring(const std::string& DateOfHiring);
	std::vector< LeaderBehavior* >  getAllLeaders();

  Employee2* FindEmployeeByLastName2( const std::string& lastName );
  LeaderBehavior* FindLeaderEmployeeByLastName( const std::string& lastName );

  int GetEmployeesCount();

	
};

class ComponyConsole
{
public:
	void PrintEmplyeesList(Company2& company);
//	void PrintLeaderBehavior(std::vector<Employee2*>  Employee2);
   void PrintSubmissedList(LeaderBehavior* leader );

	void PrintEmplyeesListBySortLastName(std::vector<Employee2*>  Employee2);
	void PrintReportRow(const std::string& pos, const std::string& lastName, const std::string& firstName, const std::string& patronymic, const std::string& dateOfBirth, const std::string& dateOfHiring);
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
