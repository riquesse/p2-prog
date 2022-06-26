#include "chartitem.h"

ChartItem::ChartItem(const std::string &name)
    : m_name(name),
      m_min(0),
      m_max(0)
{

}

std::string ChartItem::getName() const
{
    return m_name;
}

void ChartItem::setName(const std::string &name)
{
    m_name = name;
}

double ChartItem::min() const
{
    return m_min;
}

double ChartItem::max() const
{
    return m_max;
}
