#include "stdafx.h"
#include "Position.h"

bool Position::CanHaveSubmissed()
{
	return false;
}

bool LeaderPosition::CanHaveSubmissed()
{
	return true;
}
