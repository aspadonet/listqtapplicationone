#include "stdafx.h"
#include "Position.h"

Position* Position::Create(std::string posName)
{
	if ("Worker" == posName)
	{
		return new WorkerPosition();
	}
	else if ("Manager" == posName)
	{
		return new ManagerPosition();
	}
	else if ("Director" == posName)
	{
		return new DirectorPosition();
	}
	else if ("Cleaner" == posName)
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
