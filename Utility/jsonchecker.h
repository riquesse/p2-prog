#ifndef JSONCHECKER_H
#define JSONCHECKER_H

#include <QJsonObject>
#include <QJsonArray>
#include <cmath>

#include <QDebug>

class JsonChecker
{
private:
    JsonChecker();

    static bool hasValidID(double id);
    static bool hasValidCategories(QJsonArray categories);
    static bool isInteger(double number);
    static bool hasValidAxis(const QJsonObject& json);
    static bool hasValidPieChartData(const QJsonObject& json);
    static bool hasValidBarChartData(const QJsonObject& json);
    static bool hasValidLineChartData(const QJsonObject& json);

public:
    static bool isValid(const QJsonObject& json);
};

#endif // JSONCHECKER_H
