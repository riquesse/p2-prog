#include "jsonchecker.h"

JsonChecker::JsonChecker()
{

}

bool JsonChecker::hasValidID(double id)
{
    if(id < 0 || id >= 3)
        return false;

    return isInteger(id);
}

bool JsonChecker::hasValidCategories(QJsonArray categories)
{
    for(auto it = categories.begin(); it != categories.end(); ++it){
        if(!(*it).isString())
            return false;
    }
    return true;
}

bool JsonChecker::isInteger(double number)
{
    return std::trunc(number) == number;
}

bool JsonChecker::hasValidAxis(const QJsonObject &json)
{
    if(!json.contains("axis-x-title") || !json["axis-x-title"].isString())
        return false;

    if(!json.contains("axis-y-title") || !json["axis-y-title"].isString())
        return false;

    return true;
}

bool JsonChecker::hasValidBarChartData(const QJsonObject &json)
{
    if(!hasValidAxis(json))
        return false;

    if(!json.contains("barsets-number") || !json["barsets-number"].isDouble() || !isInteger(json["barsets-number"].toDouble()))
        return false;

    if(!json.contains("bars-number") ||!json["bars-number"].isDouble() || !isInteger(json["bars-number"].toDouble()))
        return false;

    if(json["categories"].toArray().size() != json["bars-number"].toDouble())
        return false;

    if(!json.contains("barsets") || !json["barsets"].isArray())
        return false;

    QJsonArray barsets = json["barsets"].toArray();
    if(json["barsets-number"].toDouble() != barsets.size())
        return false;

    for(auto it = barsets.begin(); it != barsets.end(); it++){
        QJsonObject barset = (*it).toObject();
        if(!barset.contains("barset-name") || !barset["barset-name"].isString())
            return false;

        if(!barset.contains("bars") || !barset["bars"].isArray())
            return false;

        QJsonArray bars = barset["bars"].toArray();

        if(bars.size() != json["bars-number"].toDouble())
            return false;

        for(auto it = bars.begin(); it != bars.end(); ++it){
            if(!(*it).isDouble())
                return false;
        }
    }

    return true;
}

bool JsonChecker::hasValidLineChartData(const QJsonObject &json)
{
    if(!hasValidAxis(json))
    return false;

    if(!json.contains("lines-number") || !json["lines-number"].isDouble() || !isInteger(json["lines-number"].toDouble()))
        return false;

    if(!json.contains("points-per-line") ||!json["points-per-line"].isDouble() || !isInteger(json["points-per-line"].toDouble()))
        return false;

    if(json["categories"].toArray().size() != json["points-per-line"].toDouble())
        return false;

    if(!json.contains("lines") || !json["lines"].isArray())
        return false;

    QJsonArray lines = json["lines"].toArray();
    if(json["lines-number"].toDouble() != lines.size())
        return false;

    for(auto it = lines.begin(); it != lines.end(); it++){
        QJsonObject line = (*it).toObject();
        if(!line.contains("line-name") || !line["line-name"].isString())
            return false;

        if(!line.contains("points") || !line["points"].isArray())
            return false;

        QJsonArray points = line["points"].toArray();

        if(points.size() != json["points-per-line"].toDouble())
            return false;

        for(auto it = points.begin(); it != points.end(); ++it){
            QJsonObject point = (*it).toObject();

            if(!point.contains("x") || !point["x"].isDouble() || !isInteger(point["x"].toDouble()))
                return false;

            if(!point.contains("y") || !point["y"].isDouble())
                return false;
        }
    }

    return true;
}

bool JsonChecker::hasValidPieChartData(const QJsonObject& json)
{
    if(!json.contains("slices-number") || !json["slices-number"].isDouble() || !isInteger(json["slices-number"].toDouble()))
        return false;

    if(!json.contains("values-per-slice") ||!json["values-per-slice"].isDouble() || !isInteger(json["values-per-slice"].toDouble()))
        return false;

    if(json["categories"].toArray().size() != json["values-per-slice"].toDouble())
        return false;

    if(!json.contains("slices") || !json["slices"].isArray())
        return false;

    QJsonArray slices = json["slices"].toArray();
    if(json["slices-number"].toDouble() != slices.size())
        return false;

    for(auto it = slices.begin(); it != slices.end(); it++){
        QJsonObject slice = (*it).toObject();
        if(!slice.contains("slice-name") || !slice["slice-name"].isString())
            return false;

        if(!slice.contains("values") || !slice["values"].isArray())
            return false;

        QJsonArray values = slice["values"].toArray();

        if(values.size() != json["values-per-slice"].toDouble())
            return false;

        for(auto it = values.begin(); it != values.end(); ++it){
            if(!(*it).isDouble() || (*it).toDouble() < 0)
                return false;
        }
    }

    return true;
}

bool JsonChecker::isValid(const QJsonObject &json)
{
    if(!json.contains("chart-id") || !hasValidID(json["chart-id"].toDouble()))
        return false;

    if(!json.contains("chart-title") || !json["chart-title"].isString())
        return false;

    if(!json.contains("categories") || !json["categories"].isArray() || !hasValidCategories(json["categories"].toArray()))
        return false;

    switch((int) json["chart-id"].toDouble()){
        case 0: {
            return hasValidPieChartData(json);
        }
        case 1: {
            return hasValidBarChartData(json);
        }
        case 2: {
            return hasValidLineChartData(json);
        }
        default :
            return false;
    }
}
