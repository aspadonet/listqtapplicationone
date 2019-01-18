#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"
#include "utils.h"
#include <QFile>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <QString>
#include <QtSql>

class SqlFileReadWrite
{
private:
	Company2* companySql;
	QFile* filexml;
public:
	SqlFileReadWrite(QFile* file, Company2* company);
	void ReadSqlFile();
	void WriteSqlFile();
};