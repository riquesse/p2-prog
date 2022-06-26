#include "barset.h"

BarSet::BarSet(unsigned int bars, const std::string &name)
    : ChartItem(name),
      m_bars(bars, 0)
{

}

BarSet::~BarSet()
{

}

unsigned int BarSet::count() const
{
    return m_bars.size();
}

double BarSet::getValue(unsigned int index) const
{
    if(index >= count())
        throw std::out_of_range("BarSet::getValue(unsigned int index): index out of range.");

    return m_bars.at(index);
}

void BarSet::setValue(unsigned int index, double value)
{
    if(index >= count())
        throw std::out_of_range("BarSet::setValue(unsigned int index): index out of range.");

    m_bars[index] = value;
    updateRange();
}

void BarSet::insert(unsigned int index, unsigned int n)
{
    if(index > count())
        throw std::out_of_range("BarSet::insert(unsigned int index, unsigned int): index out of range.");

    m_bars.insert(m_bars.begin()+index, n, 0);
}

void BarSet::updateRange()
{
    m_min = m_max = 0;
    for(unsigned int i = 0; i < m_bars.size(); ++i){
        double value = getValue(i);
        if(value < m_min) {
            m_min = value;
        }
        else if(value > m_max) {
            m_max = value;
        }
    }
}

void BarSet::remove(unsigned int index, unsigned int n)
{
    if(index+n > count())
        throw std::out_of_range("BarSet::remove(unsigned int index, unsigned int n): out of range.");

    auto first = m_bars.begin()+index;
    auto last = first+n;

    m_bars.erase(first, last);

    updateRange();
}

void BarSet::toJson(QJsonObject &json) const
{
    json["barset-name"] = QString::fromStdString(getName());

    QJsonArray bars;
    for(auto it = m_bars.begin(); it != m_bars.end(); ++it){
        bars.append(*it);
    }

    json["bars"] = bars;
}

void BarSet::fromJson(const QJsonObject &json)
{
    setName(json["barset-name"].toString().toStdString());

    QJsonArray bars = json["bars"].toArray();
    for(unsigned int i = 0; i < m_bars.size(); ++i) {
        m_bars.at(i) = bars.at(i).toDouble();
    }

    updateRange();
}
