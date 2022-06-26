#include "cartesianchart.h"

CartesianChart::CartesianChart(unsigned int items,
                               const std::string &title,
                               const std::string &axisXTitle,
                               const std::string &axisYTitle)
    : Chart(items, title),
      m_axisXTitle(axisXTitle),
      m_axisYTitle(axisYTitle)
{

}

std::string CartesianChart::getAxisXTitle() const
{
    return m_axisXTitle;
}

std::string CartesianChart::getAxisYTitle() const
{
    return m_axisYTitle;
}

void CartesianChart::setAxisXTitle(const std::string &title)
{
    m_axisXTitle = title;
}

void CartesianChart::setAxisYTitle(const std::string &title)
{
    m_axisYTitle = title;
}

void CartesianChart::toJson(QJsonObject &json) const
{
    Chart::toJson(json);
    json["axis-x-title"] = QString::fromStdString(m_axisXTitle);
    json["axis-y-title"] = QString::fromStdString(m_axisYTitle);
}

void CartesianChart::fromJson(const QJsonObject &json)
{
    Chart::fromJson(json);
    m_axisXTitle = json["axis-x-title"].toString().toStdString();
    m_axisYTitle = json["axis-y-title"].toString().toStdString();
}


