#include "stdafx.h"
#include "Position.h"

Position* Position::Create(std::string posName)
{
	if ("Рабочий" == posName)
	{
		return new WorkerPosition();
	}
	else if ("Менеджер" == posName)
	{
		return new ManagerPosition();
	}
	else if ("Директор" == posName)
	{
		return new DirectorPosition();
	}
	else if ("Уборщик" == posName)
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
