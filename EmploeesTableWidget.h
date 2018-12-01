#pragma once
#include "QTableWidget"
#include "Employee.h"

class EmploeesTableWidget : public QTableWidget
{
public:
	EmploeesTableWidget( std::vector< Employee2* >& emplyeesList, QWidget *parent = nullptr);
};
