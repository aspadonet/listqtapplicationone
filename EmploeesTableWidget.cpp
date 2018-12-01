#include "stdafx.h"
#include "EmploeesTableWidget.h"

EmploeesTableWidget::EmploeesTableWidget(std::vector< Employee2* >& emplyeesList, QWidget *parent )
	: QTableWidget( parent )
{
	setRowCount(emplyeesList.size());
	// ...
}
