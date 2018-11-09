#include "stdafx.h"
#include "Employee.h"


Employee2::Employee2(const std::string& lastName, Position* pos, const std::string& firstName, std::string patronymic, const std::string& dateOfBirth, const std::string& dateOfHiring)
{
	LastName = lastName;
  SetPositionName( pos );
	FirstName = firstName;
	Patronymic = patronymic;
	DateOfBirth = dateOfBirth;
	DateOfHiring = dateOfHiring;
}

std::string Employee2::GetLastName()
{
	return LastName;
}

std::string Employee2::GetFirstName()
{
	return FirstName;
}

std::string Employee2::GetPatronymic()
{
	return Patronymic;
}

std::string Employee2::GetDateOfBirth()
{
	return DateOfBirth;
}

std::string Employee2::GetDateOfHiring()
{
	return DateOfHiring;
}

std::string Employee2::GetPositionName()
{
	if (Pos == nullptr)
	{
		std::cout << "позиция не установленна" << std::endl;
	}

	return Pos->GetName();
}

void Employee2::SetPositionName(Position* newPos )
{
  if( Pos && LeaderBeh && !newPos->CanHaveSubmissed() )
  {
    delete LeaderBeh;
    LeaderBeh = nullptr;
  }

	Pos = newPos;

  if( !LeaderBeh && Pos->CanHaveSubmissed() )
  {
    LeaderBeh = new LeaderBehavior();
  }
}


std::vector<Employee2*>  Employee2::GetLeaderBehavior()
{
	
	std::vector<Employee2*>  LeadBehavior = LeaderBeh->getSubmissed();
	return LeadBehavior;
		

		
}

bool Employee2::CanHaveSubmissed() const
{
  return Pos->CanHaveSubmissed();
}

LeaderBehavior* Employee2::GetLeaderBehavior2()
{
  if( !CanHaveSubmissed() )
  {
    // ASSERT();
    return nullptr;
  }

  return LeaderBeh;
}

LeaderBehavior::LeaderBehavior()
{ }
void LeaderBehavior::DeleteSubmissed(Employee2* emp)
{
		Employee2* employees = emp;
		
			

		for (auto it = SubmissedVec.cbegin(); it != SubmissedVec.cend(); it++)
		{
			if (it == SubmissedVec.cend())
				break;

			Employee2* empl = *it;

			if (empl->GetLastName() == employees->GetLastName())
				{
					SubmissedVec.erase(it);
					break;

				}
			
		}
}
void LeaderBehavior::addSubmissed(Employee2* emp)
{
	SubmissedVec.push_back(emp);
}

std::vector<Employee2*>  LeaderBehavior::getSubmissed()
{
	return SubmissedVec;
}
