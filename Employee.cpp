#include "stdafx.h"
#include "Employee.h"
#include "utils.h"


Employee2::Employee2(const QString& lastName, Position* pos, const QString& firstName, QString patronymic, const QDate& dateOfBirth, const QDate& dateOfHiring)
{
	LastName = lastName;
  SetPositionName( pos );
	FirstName = firstName;
	Patronymic = patronymic;
	DateOfBirth = dateOfBirth;
	DateOfHiring = dateOfHiring;
}

QString Employee2::GetLastName()
{
	return LastName;
}

QString Employee2::GetFirstName()
{
	return FirstName;
}

QString Employee2::GetPatronymic()
{
	return Patronymic;
}

QDate Employee2::GetDateOfBirth()
{
	return DateOfBirth;
}

QDate Employee2::GetDateOfHiring()
{
	return DateOfHiring;
}

QString Employee2::GetPositionName()
{
	if (Pos == nullptr)
	{
		std::cout << "позиция не установленна" << std::endl;
	}
	QString qstr = toQtString(Pos->GetName());

	

	return qstr;
}
void Employee2::SetEdit(const QString& lastName, const QString& firstName, QString patronymic, const QDate& dateOfBirth, const QDate& dateOfHiring)
{
	LastName = lastName;
	FirstName = firstName;
	Patronymic = patronymic;
	DateOfBirth = dateOfBirth;
	DateOfHiring = dateOfHiring;
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
