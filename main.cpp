
#include <QtWidgets/QApplication>
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w; // ����� constructor
	
	w.resize(700, 800);
	w.show();

	

	return a.exec();
}