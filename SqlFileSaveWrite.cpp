#include "SqlFileSaveWrite.h"

SqlFileReadWrite::SqlFileReadWrite(QFile* file, Company2* company)
{
	companySql = company;
}
void SqlFileReadWrite::ReadSqlFile()
{

}
void SqlFileReadWrite::WriteSqlFile() 
{
	QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
	dbase.setDatabaseName("mybd.sqlite");
	if (!dbase.open()) {

	}
	for (Employee2* emptemp : companySql->GetEmployees())
	{
		int posId = 0;
		{
			QSqlQuery query(dbase);

			query.prepare("SELect id from positions where name = ?");
			query.addBindValue(emptemp->GetPositionName());

			query.next();
			posId = query.value(0).toInt();
		}

		QSqlQuery query(dbase);
		query.prepare("INSERT INTO EmployeeBd(PositionBd, lastNameBd , firstNameBd, patronymicBd, DateOfBirthBd, DateOfHiring)"
			"VALUES (?, ?, ?, ?, ?, ?)");
		query.addBindValue(posId);
		query.addBindValue(emptemp->GetLastName());
		query.addBindValue(emptemp->GetFirstName());
		query.addBindValue(emptemp->GetPatronymic());
		query.addBindValue(emptemp->GetDateOfBirth());
		query.addBindValue(emptemp->GetDateOfHiring());
		query.exec();

		//		emptemp->SetId(query.lastInsertId());
	}

	for (Employee2* leaderEmp : companySql->GetEmployees())
	{
		//		LeaderBehavior* leader = leaderEmp->GetLeaderBehavior();
		//
		//		for (Employee2* childEmp : leader->getSubmissed())
		//		{
		//			QSqlQuery query(dbase);
		//			query.prepare("INSERT INTO LeaderBeh(ParentId, Childid)"
		//				"VALUES (?, ?)");
		//			query.addBindValue(leaderEmp->GetId());
		//			query.addBindValue(childEmp->GetId());
		//			query.exec();
		//		}
	}


	QSqlDatabase dsub = QSqlDatabase::addDatabase("QSQLITE");
	dsub.setDatabaseName("leadbd.sqlite");
	QSqlQuery quer(dsub);
	if (!dbase.open()) {
		QMessageBox msgBox;
		msgBox.setWindowTitle("ERROR");
		msgBox.setText(QString::fromLocal8Bit("ERROR"));
		msgBox.exec();

		return;
	}
	quer.prepare("INSERT INTO LeaderBehavior()" "VALUES (?, ?)");
	quer.addBindValue(3);
	quer.addBindValue(4);
	quer.exec();
}