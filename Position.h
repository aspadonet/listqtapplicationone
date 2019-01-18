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
	virtual std::string GetName() override { return "Рабочий"; }
};

class CleanerPosition : public Position
{
public:
	virtual std::string GetName() override { return "Уборщик"; }
};

class ManagerPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "Менеджер"; }
};

class DirectorPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "Директор"; }
};
