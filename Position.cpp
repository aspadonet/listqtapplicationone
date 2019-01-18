#include "stdafx.h"
#include "Position.h"

Position* Position::Create(std::string posName)
{
	if ("�������" == posName)
	{
		return new WorkerPosition();
	}
	else if ("��������" == posName)
	{
		return new ManagerPosition();
	}
	else if ("��������" == posName)
	{
		return new DirectorPosition();
	}
	else if ("�������" == posName)
	{
		return new CleanerPosition();
	}

	throw std::logic_error("unknown position");
}

bool Position::CanHaveSubmissed()
{
	return false;
}

bool LeaderPosition::CanHaveSubmissed()
{
	return true;
}
