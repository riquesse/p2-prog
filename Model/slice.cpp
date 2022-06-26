#include "slice.h"

Slice::Slice(unsigned int valuesPerSlice, const std::string &name)
    : ChartItem(name),
      m_values(valuesPerSlice, 0)
{

}

unsigned int Slice::count() const
{
    return m_values.size();
}

double Slice::getValue(unsigned int index) const
{
    if(index >= count())
        throw std::out_of_range("Slice::getValue(unsigned int index): index out of range.");

    return m_values[index];
}

void Slice::setValue(unsigned int index, double value)
{
    if(index >= count())
        throw std::out_of_range("Slice::setValue(unsigned int index, double value): index out of range.");

    m_values[index] = value;
    updateRange();
}

void Slice::insert(unsigned int index, unsigned int n)
{
    if(index > count())
        throw std::out_of_range("Slice::insert(unsigned int index, unsigned int n): index out of range.");

    m_values.insert(m_values.begin()+index, n, 0);
}

void Slice::updateRange()
{
    m_min = m_max = 0;
    for(unsigned int i = 0; i < m_values.size(); ++i){
        double value = getValue(i);
        if(value < m_min) {
            m_min = value;
        }
        else if(value > m_max) {
            m_max = value;
        }
    }
}

void Slice::remove(unsigned int index, unsigned int n)
{
    if(index+n > count())
        throw std::out_of_range("Slice::remove(unsigned int index, unsigned int n): out of range.");

    auto first = m_values.begin()+index;
    auto last = first+n;

    m_values.erase(first, last);

    updateRange();
}

void Slice::toJson(QJsonObject &json) const
{
    json["slice-name"] = QString::fromStdString(getName());

    QJsonArray values;
    for(auto it = m_values.begin(); it != m_values.end(); ++it){
        values.append(*it);
    }
    json["values"] = values;
}

void Slice::fromJson(const QJsonObject &json)
{
    setName(json["slice-name"].toString().toStdString());

    QJsonArray values = json["values"].toArray();
    for(unsigned int i = 0; i < m_values.size(); ++i){
        m_values.at(i) = values.at(i).toDouble();
    }

    updateRange();
}
