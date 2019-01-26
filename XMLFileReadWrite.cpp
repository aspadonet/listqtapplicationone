#include "XMLFileReadWrite.h"

XMLFileReadWrite::XMLFileReadWrite(QFile* file, Company2* company)
{
	companyXML = company;
	filexml = file;
};

XMLFileReadWrite::~XMLFileReadWrite()
{
}


//#define FIRST_NAME "FirstName"

namespace
{
	const char* cPositionName = "PositionName";
	const char* cFirstName = "FirstName";
	const char* cLastName = "LastName";
	const char* cPatronymic = "Patronymic";
	const char* cDateOfBirth = "DateOfBirht";
	const char* cDateOfHiring = "DateOfHiring";
}


void XMLFileReadWrite::WriterXMLFile()
{
	QXmlStreamWriter xmlWriter(filexml);

	xmlWriter.setAutoFormatting(true);
	
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement("ONE");

	for (Employee2* emp2 : companyXML->GetEmployees())
	{
		xmlWriter.writeStartElement("Employee");
		xmlWriter.writeTextElement(cPositionName, (emp2->GetPositionName()));
		xmlWriter.writeTextElement(cLastName, (emp2->GetLastName()));
		xmlWriter.writeTextElement(cFirstName, (emp2->GetFirstName()));
		xmlWriter.writeTextElement(cPatronymic, (emp2->GetPatronymic()));
		xmlWriter.writeTextElement(cDateOfBirth, (emp2->GetDateOfBirth().toString(Qt::ISODate)));
		xmlWriter.writeTextElement(cDateOfHiring, (emp2->GetDateOfHiring().toString(Qt::ISODate)));

		if (emp2->CanHaveSubmissed())
		{
			if (!emp2->GetLeaderBehavior2()->getSubmissed().empty())
			{
				xmlWriter.writeStartElement("SubmissedEmployes");
				
				std::vector <Employee2*> EmpAssociate = emp2->GetLeaderBehavior2()->getSubmissed();
				
				for (Employee2* emp2 : EmpAssociate)
				{
					xmlWriter.writeStartElement("Employee");
					xmlWriter.writeTextElement(cPositionName, (emp2->GetPositionName()));
					xmlWriter.writeTextElement(cLastName, (emp2->GetLastName()));
					xmlWriter.writeTextElement(cFirstName, (emp2->GetFirstName()));
					xmlWriter.writeTextElement(cPatronymic, (emp2->GetPatronymic()));
					xmlWriter.writeTextElement(cDateOfBirth, (emp2->GetDateOfBirth().toString(Qt::ISODate)));
					xmlWriter.writeTextElement(cDateOfHiring, (emp2->GetDateOfHiring().toString(Qt::ISODate)));					
					xmlWriter.writeEndElement();
				}
				xmlWriter.writeEndElement();
			}
		}
		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndElement();
}

void XMLFileReadWrite::ReadXMLFile()
{
	submissedToMananger.clear();

	QXmlStreamReader Rxml;

	Rxml.setDevice(filexml);

	Rxml.readNext();

	Rxml.readNext();

	if (Rxml.name() == "ONE")
	{
		readONE(Rxml);
	}
	else
	{
		throw std::logic_error("wrong xml");
	}
	
}

void XMLFileReadWrite::readONE(QXmlStreamReader& xml )
{
	Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("ONE"));

	while (xml.readNextStartElement()) // Employee
	{
		if (xml.name() == QLatin1String("Employee"))

			readEmployee( xml );

		else
		{
			// ������� ����������
			xml.skipCurrentElement();
		}
	
	}


	for (auto it = submissedToMananger.cbegin(); it != submissedToMananger.cend(); ++it)
	{
		QString submissed = it->first;

		QString manager = it->second;

		companyXML->AssociateAnEmployeeWithAManager(manager, submissed);
	}

}

void XMLFileReadWrite::readEmployee(QXmlStreamReader& xml)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Employee"));

	QString empLastName;
	QString empFirstName;
	QString empPatronimic;
	//QString SubmissedEmployes;
	QDate DateOfBirth;
	QDate DateOfHiring;
	Position* pos = nullptr;
	std::vector< Employee2 > submissedEmployes;

	while (xml.readNextStartElement()) // PositionName, LastName, ..., SubmissedEmployes
	{
		submissedEmployes.clear();

		bool anyFiledReaded = readPosition(xml, &pos)
			|| readTextField(xml, cLastName, empLastName)
			|| readTextField(xml, cFirstName, empFirstName)
			|| readTextField(xml, cPatronymic, empPatronimic)
			|| readDateElem(xml, cDateOfBirth, DateOfBirth)
			|| readDateElem(xml, cDateOfHiring, DateOfHiring)
			|| readSubmissedEmployes(xml, "SubmissedEmployes" , submissedEmployes);

		if( !anyFiledReaded ){
			// ������� ����������
			xml.skipCurrentElement();
			//readNextStartElement
		}
	}

	if (empLastName.isEmpty() || DateOfHiring.isNull())

		throw std::logic_error("wrong xml");

	Employee2* emp = new Employee2( empLastName, pos, empFirstName, empPatronimic, DateOfBirth, DateOfHiring);

	companyXML->AddEmployeeFromFile(emp);

	for (Employee2 submissed : submissedEmployes)
	{
		submissedToMananger[submissed.GetLastName()] = empLastName;
	}

	/*if (SubmissedEmployes == "SubmissedEmployes")
	{
		readSubmissedEmployes(xml, empLastName);
	}*/

	/*LeaderBehavior* leader = emp->GetLeaderBehavior2();
	if (leader)
	{
		for (Employee2* submissedEmp : submissedEmployes)
			leader->addSubmissed(submissedEmp);
	}*/
	
	//emplyeesVec.push_back(emp);
}

bool XMLFileReadWrite::readTextField(QXmlStreamReader& xml, const char* name, QString& filed)
{
	if (xml.name() != toQtString( name ) )
		return false;

	filed = xml.readElementText();
	//xml.readNextStartElement();
	return true;
}

bool XMLFileReadWrite::readPosition(QXmlStreamReader& xml, Position** pos)
{
	if (xml.name() != QLatin1String(cPositionName))
		return false;

	QString posName = xml.readElementText();

	*pos = Position::Create(toStdString(posName));

	//xml.readNextStartElement();
	return true;
}

bool XMLFileReadWrite::readDateElem(QXmlStreamReader& xml, const char* name, QDate& filed)
{
	if (xml.name() != toQtString(name))
		return false;
	filed = QDate::fromString((xml.readElementText()), Qt::ISODate);
	//xml.readNextStartElement();
	return true;
}
bool XMLFileReadWrite::readSubmissedEmployes(QXmlStreamReader& xml, const char* name, std::vector< Employee2>& submissedEmpVec )
{
	while (xml.readNextStartElement()) // Employee
	{

		QString empLastName;
		QString empFirstName;
		QString empPatronimic;
		QDate DateOfBirth;
		QDate DateOfHiring;
		Position* pos = nullptr;
		//std::vector< Employee2 > submissedEmployes;

		while (xml.readNextStartElement()) // PositionName, LastName, ...
		{
			bool anyFiledReaded = readPosition(xml, &pos)
				|| readTextField(xml, cLastName, empLastName)
				|| readTextField(xml, cFirstName, empFirstName)
				|| readTextField(xml, cPatronymic, empPatronimic)
				|| readDateElem(xml, cDateOfBirth, DateOfBirth)
				|| readDateElem(xml, cDateOfHiring, DateOfHiring);
			
			if (!anyFiledReaded) {
				// ������� ����������
				xml.skipCurrentElement();
				//readNextStartElement
			}
		}

		if (empLastName.isEmpty() || DateOfHiring.isNull())
			throw std::logic_error("wrong xml");

		Employee2 emp(empLastName, pos, empFirstName, empPatronimic, DateOfBirth, DateOfHiring);
//		companyXML->AddEmployeeFromFile(emp);

		submissedEmpVec.push_back(emp);

	}

//	if (!companyXML->AddEmployeeFromFile(emp))
//	{
//		delete emp;
//	}

//	companyXML->AssociateAnEmployeeWithAManager(filed, empLastName);
	return true;
}
