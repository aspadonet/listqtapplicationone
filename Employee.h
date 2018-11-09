#pragma once

#include <string>
#include "Position.h"

class LeaderBehavior;

class Employee2
{
protected:
	Position* Pos = nullptr;
	LeaderBehavior* LeaderBeh = nullptr;
	std::string LastName;
	std::string FirstName;
	std::string Patronymic;
	std::string DateOfBirth;
	std::string DateOfHiring;

public:
	
	Employee2(const std::string& lastName, Position* pos, const std::string& firstName, std::string patronymic, const std::string& DateOfBirth, const std::string& DateOfHiring);

	std::string GetLastName();
	std::string GetFirstName();
	std::string GetPatronymic();
	std::string GetDateOfBirth();
	std::string GetDateOfHiring();
	std::string GetPositionName();
	void SetPositionName(Position* pos);
	std::vector<Employee2*>  GetLeaderBehavior();

  bool CanHaveSubmissed() const;
  LeaderBehavior* GetLeaderBehavior2();
};

class LeaderBehavior
{
public:
	LeaderBehavior();
	void addSubmissed( Employee2* emp );
	void DeleteSubmissed(Employee2* emp);
	std::vector<Employee2*>  getSubmissed();
	std::vector<Employee2*>  SubmissedVec;
};
