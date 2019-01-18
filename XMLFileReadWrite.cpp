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
//
//namespace
//{
//	const char* cFirstName = "FirstName";
//}


void XMLFileReadWrite::WriterXMLFile()
{
	QXmlStreamWriter xmlWriter(filexml);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement("ONE");

	for (Employee2* emp2 : companyXML->GetEmployees())
	{
		xmlWriter.writeStartElement("Employee");
		xmlWriter.writeTextElement("PositionName", (emp2->GetPositionName()));
		xmlWriter.writeTextElement("LastName", (emp2->GetLastName()));
		xmlWriter.writeTextElement("FirstName", (emp2->GetFirstName()));
		xmlWriter.writeTextElement("Patronymic", (emp2->GetPatronymic()));
		xmlWriter.writeTextElement("DateOfBirth", (emp2->GetDateOfBirth().toString(Qt::ISODate)));
		xmlWriter.writeTextElement("DateOfHiring", (emp2->GetDateOfHiring().toString(Qt::ISODate)));

		if (emp2->CanHaveSubmissed())
		{
			if (!emp2->GetLeaderBehavior2()->getSubmissed().empty())
			{


				xmlWriter.writeStartElement("SubmissedEmployes");
				
				std::vector <Employee2*> EmpAssociate = emp2->GetLeaderBehavior2()->getSubmissed();
				for (Employee2* emp2 : EmpAssociate)
				{
					xmlWriter.writeStartElement("Employee");

					xmlWriter.writeTextElement("PositionName", (emp2->GetPositionName()));
					xmlWriter.writeTextElement("LastName", (emp2->GetLastName()));
					xmlWriter.writeTextElement("FirstName", (emp2->GetFirstName()));
					xmlWriter.writeTextElement("Patronymic", (emp2->GetPatronymic()));
					xmlWriter.writeTextElement("DateOfBirth", (emp2->GetDateOfBirth().toString(Qt::ISODate)));
					xmlWriter.writeTextElement("DateOfHiring", (emp2->GetDateOfHiring().toString(Qt::ISODate)));
					
					xmlWriter.writeEndElement();
				}
				//temp2 = "Close Associate An Employee With " + toStdString(emp2->GetLastName()) + "\n";
				
				xmlWriter.writeEndElement();
			}
		}

		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndElement();
}

void XMLFileReadWrite::ReadXMLFile()
{
	//companyXML.DeleteEmployeALL();

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
			// генерим исключение
			xml.skipCurrentElement();
		}
	}


	for (auto it = submissedToMananger.begin(); it != submissedToMananger.begin(); ++it)
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
	QString SubmissedEmployes;
	QDate DateOfBirth;
	QDate DateOfHiring;
	Position* pos = nullptr;
	std::vector< Employee2 > submissedEmployes;

	while (xml.readNextStartElement()) // PositionName, LastName, ..., SubmissedEmployes
	{
		submissedEmployes.clear();

		bool anyFiledReaded = readPosition(xml, &pos)
			|| readTextField(xml, "LastName", empLastName)
			|| readTextField(xml, "FistName", empFirstName)
			|| readTextField(xml, "Patronymic", empPatronimic)
			|| readDateElem(xml, "DateOfBirth", DateOfBirth)
			|| readDateElem(xml, "DateOfHiring", DateOfHiring)
			|| readSubmissedEmployes(xml, "SubmissedEmployes" , submissedEmployes);

		if( !anyFiledReaded ){
			// генерим исключение
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

//void XMLFileReadWrite::readSubmissedEmployes(QXmlStreamReader& xml,QString empLastNameLead)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("Employee"));
//
//	QString empLastName;
//	QString empFirstName;
//	QString empPatronimic;
//	QString SubmissedEmployes;
//	QDate DateOfBirth;
//	QDate DateOfHiring;
//	Position* pos = nullptr;
//	//std::vector< Employee2 > submissedEmployes;
//
//	while (xml.readNextStartElement())
//	{
//		bool anyFiledReaded = readPosition(xml, &pos)
//			|| readDateElem(xml, "DateOfBirth", DateOfBirth)
//			|| readDateElem(xml, "DateOfHiring", DateOfHiring)
//			|| readTextField(xml, "LastName", empLastName)
//			|| readTextField(xml, "FirstName", empFirstName)
//			|| readTextField(xml, "Patronimic", empPatronimic)			
//			|| readSubmissedEmployes(xml, "SubmissedEmployes", SubmissedEmployes);
//
//		if (!anyFiledReaded) {
//			// генерим исключение
//			xml.skipCurrentElement();
//		}
//	}
//
//	if (empLastName.isEmpty() || DateOfHiring.isNull())
//		throw std::logic_error("wrong xml");
//
//	Employee2* emp = new Employee2(empLastName, pos, empFirstName, empPatronimic, DateOfBirth, DateOfHiring);
//	companyXML->AddEmployee(emp);
//	
////	companyXML->AssociateAnEmployeeWithAManager(empLastNameLead, empLastName);
//}

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
	if (xml.name() != QLatin1String("PositionName"))
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
		QString SubmissedEmployes;
		QDate DateOfBirth;
		QDate DateOfHiring;
		Position* pos = nullptr;
		//std::vector< Employee2 > submissedEmployes;

		while (xml.readNextStartElement()) // PositionName, LastName, ...
		{
			bool anyFiledReaded = readPosition(xml, &pos)
				|| readTextField(xml, "LastName", empLastName)
				|| readTextField(xml, "FirstName", empFirstName)
				|| readTextField(xml, "Patronymic", empPatronimic)
				|| readDateElem(xml, "DateOfBirth", DateOfBirth)
				|| readDateElem(xml, "DateOfHiring", DateOfHiring);
			//			|| readSubmissedEmployes(xml, "SubmissedEmployes", empLastName);

			if (!anyFiledReaded) {
				// генерим исключение
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
