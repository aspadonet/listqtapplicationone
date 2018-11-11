#pragma once

#include <QString>

QString toQtString(const char* s)
{
	return QString::fromLocal8Bit(s);
}

QString toQtString(const std::string& s)
{
	return QString::fromLocal8Bit(s.c_str());
}
