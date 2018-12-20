#pragma once

#include <QString>

QString toQtString(const char* s);
QString toQtString(const std::string& s);

std::string toStdString(const QString& s);


