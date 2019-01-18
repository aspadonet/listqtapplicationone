#pragma once

#include <string>
#include "Position.h"
#include <QString>
#include <QDate>

class LeaderBehavior;

class Employee2
{
protected:
	long Id;
	Position* Pos = nullptr;
	LeaderBehavior* LeaderBeh = nullptr;
	QString LastName;
	QString FirstName;
	QString Patronymic;
	QDate DateOfBirth;
	QDate DateOfHiring;

public:
	
	Employee2(const QString& lastName, Position* pos, const QString& firstName, QString patronymic, const QDate& DateOfBirth, const QDate& DateOfHiring);

	QString GetLastName();
	QString GetFirstName();
	QString GetPatronymic();
	QDate GetDateOfBirth();
	QDate GetDateOfHiring();
	QString GetPositionName();
	void SetPositionName(Position* pos);
	void SetEdit(const QString& lastName,  const QString& firstName, QString patronymic, const QDate& DateOfBirth, const QDate& DateOfHiring);
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
