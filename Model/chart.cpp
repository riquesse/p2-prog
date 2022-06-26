#include "chart.h"

Chart::Chart(unsigned int items, const std::string &title)
    : m_items(items),
      m_title(title)
{

}

Chart::~Chart()
{
    for(auto it = m_items.begin(); it != m_items.end(); ++it)
        delete *it;
}

unsigned int Chart::count() const
{
    return m_items.size();
}

unsigned int Chart::countPerItem() const
{
    return count() > 0 ? itemAt(0)->count() : 0;
}

void Chart::remove(unsigned int index, unsigned int n)
{
    if(index + n > count())
        throw std::out_of_range("Chart::removeSlices(unsigned int index, unsigned int n): out of range.");

    auto first = m_items.begin()+index;
    auto last = first+n;

    m_items.erase(first, last);
}

void Chart::setTitle(const std::string &title)
{
    m_title = title;
}

std::string Chart::getTitle() const
{
    return m_title;
}

void Chart::toJson(QJsonObject &json) const
{
    json["chart-title"] = QString::fromStdString(m_title);
}

void Chart::fromJson(const QJsonObject &json)
{
    m_title = json["chart-title"].toString().toStdString();
}

double Chart::min() const
{
    double min = 0;
    for(auto it = m_items.begin(); it != m_items.end(); ++it){
        double value = (*it)->min();
        if(value < min) {
            min = value;
        }
    }
    return min;
}

double Chart::max() const
{
    double max = 0;
    for(auto it = m_items.begin(); it != m_items.end(); ++it){
        double value = (*it)->max();
        if(value > max) {
            max = value;
        }
    }
    return max;
}

ChartItem *Chart::itemAt(unsigned int index) const
{
    if(index >= count())
        throw std::out_of_range("Chart::itemAt(unsigned int index): index out of range.");

    return m_items[index];
}
