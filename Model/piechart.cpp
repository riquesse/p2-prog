#include "piechart.h"

PieChart::PieChart(unsigned int slices,
                   unsigned int valuesPerSlice,
                   const std::string &title)
    : Chart(slices, title)
{
    for(auto it = m_items.begin(); it != m_items.end(); ++it)
        *it = new Slice(valuesPerSlice);
}

Slice *PieChart::itemAt(unsigned int index) const
{
    if(index >= count())
            throw std::out_of_range("PieChart::itemAt(unsigned int index): index out of range.");

        return dynamic_cast<Slice*>(Chart::itemAt(index));
}

void PieChart::insert(unsigned int index, unsigned int n)
{
    if(index > count())
        throw std::out_of_range("PieChart::insertSlices(unsigned int index, unsigned int n): index out of range.");

    m_items.insert(m_items.begin()+index, n, new Slice(countPerItem()));
}

void PieChart::toJson(QJsonObject &json) const
{
    Chart::toJson(json);

    json["chart-id"] = 0;
    json["slices-number"] = (int) count();
    json["values-per-slice"] = (int) countPerItem();

    QJsonArray slices;
    for(auto it = m_items.begin(); it != m_items.end(); ++it){
        QJsonObject slice;
        (*it)->toJson(slice);
        slices.append(slice);
    }

    json["slices"] = slices;
}

void PieChart::fromJson(const QJsonObject &json)
{
    Chart::fromJson(json);

    QJsonArray slices = json["slices"].toArray();
    for(unsigned int i = 0; i < m_items.size(); ++i){
        m_items.at(i)->fromJson(slices.at(i).toObject());
    }
}
