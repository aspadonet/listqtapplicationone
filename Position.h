#pragma once

class Position
{
public:
	virtual std::string GetName() = 0;

	virtual bool CanHaveSubmissed();
};

class LeaderPosition : public Position
{
public:
	virtual bool CanHaveSubmissed() override;
};

class WorkerPosition : public Position
{
public:
	virtual std::string GetName() override { return "�������"; }
};

class CleanerPosition : public Position
{
public:
	virtual std::string GetName() override { return "�������"; }
};

class ManagerPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "��������"; }
};

class DirectorPosition : public LeaderPosition
{
public:
	virtual std::string GetName() override { return "��������"; }
};
