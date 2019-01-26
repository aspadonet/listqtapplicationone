#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>
#include "Employee.h"
#include "Company.h"
#include "utils.h"
#include <QFile>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include "XMLFileReadWrite.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <QString>

class XMLFileReadWrite
{
private:
	Company2* companyXML;
	QFile* filexml;
public:
	XMLFileReadWrite(QFile* file, Company2* company);
	~XMLFileReadWrite();
	void WriterXMLFile();
	void ReadXMLFile();
	void readONE(QXmlStreamReader& xml);
	void readEmployee(QXmlStreamReader& xml);
//	void readSubmissedEmployes(QXmlStreamReader& xml, QString LastName);
	bool readTextField(QXmlStreamReader& xml, const char* name, QString& filed);
	bool readSubmissedEmployes(QXmlStreamReader& xml, const char* name, std::vector< Employee2>& submissedEmpVec );
	bool readPosition(QXmlStreamReader& xml, Position** pos);
	bool readDateElem(QXmlStreamReader& xml, const char* name, QDate& filed);

	//      submiised, manager
	
	std::map< QString, QString > submissedToMananger;
};