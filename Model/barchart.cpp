#include "barchart.h"

BarChart::BarChart(unsigned int barSets,
                   unsigned int bars,
                   const std::string &title,
                   const std::string &axisXTitle,
                   const std::string &axisYTitle)

    : CartesianChart(barSets, title, axisXTitle, axisYTitle)
{
    for(auto it = m_items.begin(); it != m_items.end(); ++it)
        *it = new BarSet(bars);
}

BarSet *BarChart::itemAt(unsigned int index) const
{
    if(index >= count())
        throw std::out_of_range("BarChart::itemAt(unsigned int index): index out of range.");

    return dynamic_cast<BarSet*>(Chart::itemAt(index));
}

void BarChart::insert(unsigned int index, unsigned int n)
{
    if(index > count())
        throw std::out_of_range("BarChart::insert(unsigned int index, unsigned int n) : index out of range.");

    m_items.insert(m_items.begin()+index, n, new BarSet(countPerItem()));
}

void BarChart::toJson(QJsonObject &json) const
{
    CartesianChart::toJson(json);

    json["chart-id"] = 1;
    json["barsets-number"] = (int) count();
    json["bars-number"] = (int) countPerItem();

    QJsonArray barsets;
    for(auto it = m_items.begin(); it != m_items.end(); ++it){
        QJsonObject barset;
        (*it)->toJson(barset);
        barsets.append(barset);
    }

    json["barsets"] = barsets;
}

void BarChart::fromJson(const QJsonObject &json)
{
    CartesianChart::fromJson(json);

    QJsonArray barsets = json["barsets"].toArray();
    for(unsigned int i = 0; i < m_items.size(); ++i) {
        m_items.at(i)->fromJson(barsets.at(i).toObject());
    }
}
