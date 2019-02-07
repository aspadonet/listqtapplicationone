#include "SqlFileSaveWrite.h"

SqlFileReadWrite::SqlFileReadWrite(Company2* company)
{
	companySql = company;
}
void SqlFileReadWrite::ReadSqlFile()
{
	QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
	dbase.setDatabaseName("mybd.sqlite");
	if (!dbase.open()) {
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("ERROR"));
		msgBox.exec();

		return;
	}
	QString empLastName;
	QString empLastNameMenager;
	QString empLastNameEmployee;
	QString empFirstName;
	QString empPatronimic;
	QDate DateOfBirth;
	QDate DateOfHiring;
	int ipos;
	long lId;
	QString posName;
	Position* pPos;
	{
		QSqlQuery query(dbase);

		query.exec("SELECT * FROM EMPLOYEE");

		while (query.next()) {
			lId = query.value(0).toInt();
			ipos = query.value(1).toInt();
			empLastName = query.value(2).toString();
			empFirstName = query.value(3).toString();
			empPatronimic = query.value(4).toString();
			DateOfBirth = query.value(5).toDate();
			DateOfHiring = query.value(6).toDate();
			{
				QSqlQuery query(dbase);

				query.prepare("SELECT * FROM POSITIONS WHERE ID = ?");
				query.addBindValue(ipos);
				query.exec();
				query.last();
				posName = query.value(1).toString();
				pPos = Position::Create(toStdString(posName));
			}

			Employee2* emp = new Employee2(lId, empLastName, pPos, empFirstName, empPatronimic, DateOfBirth, DateOfHiring);

			companySql->AddEmployeeFromFile(emp);
		}
	}
	{
		int idLastNameMenager;
		int idLastNameEmployee;

		QSqlQuery query(dbase);

		query.exec("SELECT * FROM LEADERBEH");
		while (query.next()) 
		{
			idLastNameMenager = query.value(1).toInt();
			{
												
						QSqlQuery query(dbase);

						query.prepare("SELECT * FROM EMPLOYEE WHERE ID = ?");
						query.addBindValue(idLastNameMenager);
						query.exec();
						query.last();
						empLastNameMenager = query.value(2).toString();
						
					
			}
			idLastNameEmployee = query.value(2).toInt();
			{
				
				QSqlQuery query(dbase);

				query.prepare("SELECT * FROM EMPLOYEE WHERE ID = ?");
				query.addBindValue(idLastNameEmployee);
				query.exec();
				query.last();
				empLastNameEmployee = query.value(2).toString();


			}
			companySql->AssociateAnEmployeeWithAManager(empLastNameMenager, empLastNameEmployee);
		}

	
	}

}
void SqlFileReadWrite::WriteSqlFile() 
{
	QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
	dbase.setDatabaseName("mybd.sqlite");
	if (!dbase.open()) {
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("ERROR"));
		msgBox.exec();

		return;
	}

	for (Employee2* emptemp : companySql->GetEmployees())
	{
		int posId = 0;
		{
			QSqlQuery query(dbase);

			query.prepare("SELECT * FROM POSITIONS WHERE NAME = ?");
			QString qstr = emptemp->GetPositionName();
			query.addBindValue(qstr);
			query.exec();
			query.last();
			posId = query.value(0).toInt();
			
			
		}
		long Id = 0;
		QSqlQuery query(dbase);
		query.prepare("INSERT INTO EMPLOYEE(POSITION_ID, LASTNAME , FIRSTNAME, PATRONYMIC, DATEOFBIRTH, DATEOFHIRING)"
			"VALUES (?, ?, ?, ?, ?, ?)");
		query.addBindValue(posId);
		query.addBindValue(emptemp->GetLastName());
		query.addBindValue(emptemp->GetFirstName());
		query.addBindValue(emptemp->GetPatronymic());
		query.addBindValue(emptemp->GetDateOfBirth());
		query.addBindValue(emptemp->GetDateOfHiring());
		query.exec();
		query.last();
		//Id = query.value(0).toInt;
		//query.lastInsertId();
		Id = query.lastInsertId().toLongLong();
		//query.exec();
		emptemp->SetId(Id);
	}

	for (Employee2* leaderEmp : companySql->getAllEmployeeLeaders())
	{
		std::vector<Employee2*> leader = leaderEmp->GetLeaderBehavior();

		for (auto it = leader.cbegin(); it != leader.cend(); it++)
		{
			if (it == leader.cend())
				break;

			Employee2* childEmp = *it;

			QSqlQuery query(dbase);
			query.prepare("INSERT INTO LEADERBEH(PARENT_ID, CHILD_ID)"
				"VALUES (?, ?)");
			query.addBindValue(leaderEmp->GetId());
			query.addBindValue(childEmp->GetId());
			query.exec();

		}
		/*for (Employee2* childEmp : leader)
		{
			QSqlQuery query(dbase);
			query.prepare("INSERT INTO LEADERBEH(PARENTID, CHILDID)"
				"VALUES (?, ?)");
			query.addBindValue(leaderEmp->GetId());
			query.addBindValue(childEmp->GetId());
			query.exec();
		}*/
	}
	   	  	
}