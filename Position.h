#pragma once
#include <QString>

class Position
{
public:
	virtual std::string GetName() = 0;

	virtual bool CanHaveSubmissed();

	static Position* Create(std::string posName);
};

class LeaderPosition : public Position
{
public:
	virtual bool CanHaveSubmissed() override;
};

class WorkerPosition : public Position
{
public:
	virtual std::string GetName() override { return "Worker"; }
};

class CleanerPosition : public Position
{
public:
	virtual std::string GetName() override { return "Cleaner"; }
};

class ManagerPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "Manager"; }
};

class DirectorPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "Director"; }
};
