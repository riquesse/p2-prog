#include "line.h"

Line::Line(unsigned int pointsPerLine, const std::string &name) :
    ChartItem(name),
    m_points(pointsPerLine, Point())
{
    for(unsigned int i=0; i<m_points.size(); ++i)
        m_points[i].setX(i);
}

unsigned int Line::count() const
{
    return m_points.size();
}

double Line::getX(unsigned int index) const
{
    if(index >= m_points.size())
        throw std::out_of_range("Line::getX(unsigned int index): index out of range.");

    return m_points[index].getX();
}

double Line::getY(unsigned int index) const
{
    if(index >= m_points.size())
        throw std::out_of_range("Line::getY(unsigned int index): index out of range.");

    return m_points[index].getY();
}

void Line::setX(unsigned int index, double value)
{
    if(index >= m_points.size())
        throw std::out_of_range("Line::setX(unsigned int index, double value): index out of range.");

    m_points[index].setX(value);
}

void Line::setY(unsigned int index, double value)
{
    if(index >= m_points.size())
        throw std::out_of_range("Line::setY(unsigned int index, double value): index out of range.");

    m_points[index].setY(value);
}

double Line::getValue(unsigned int index) const
{
    if(index >= m_points.size())
        throw std::out_of_range("Line::getValue(unsigned int index): index out of range.");

    return getY(index);
}

void Line::updateRange()
{
    m_min = m_max = 0;
    for(unsigned int i = 0; i < m_points.size(); ++i){
        double value = getValue(i);
        if(value < m_min) {
            m_min = value;
        }
        else if(value > m_max) {
            m_max = value;
        }
    }
}

void Line::setValue(unsigned int index, double value)
{
    setY(index,value);
    updateRange();
}

void Line::insert(unsigned int index, unsigned int n)
{
    if(index > m_points.size())
        throw std::out_of_range("Line::insert(unsigned int index, unsigned int n): index out of range.");

    m_points.insert(m_points.begin()+index, n, Point());

    for(unsigned int i=index; i<m_points.size(); i++){
        m_points[i].setX(i);
    }
}

void Line::remove(unsigned int index, unsigned int n)
{
    if(index+n > m_points.size())
        throw std::out_of_range("Line::remove(unsigned int index, unsigned int n): out of range.");

    auto first = m_points.begin()+index;
    auto last = first + n;

    m_points.erase(first, last);

    for(unsigned int i=index; i<m_points.size(); ++i)
        m_points[i].setX(i);

    updateRange();
}

void Line::toJson(QJsonObject &json) const
{
    json["line-name"] = QString::fromStdString(getName());

    QJsonArray points;
    for(auto it = m_points.begin(); it != m_points.end(); ++it){
        QJsonObject point;
        point["x"] = it->getX();
        point["y"] = it->getY();
        points.append(point);
    }

    json["points"] = points;
}

void Line::fromJson(const QJsonObject &json)
{
    setName(json["line-name"].toString().toStdString());

    QJsonArray points = json["points"].toArray();

    for(unsigned int i = 0; i < m_points.size(); ++i) {
        QJsonObject point = points.at(i).toObject();
        m_points[i].setX(point["x"].toDouble());
        m_points[i].setY(point["y"].toDouble());
    }

    updateRange();
}

Line::Point::Point(double x, double y)
    : m_x(x),
      m_y(y)
{

}

double Line::Point::getX() const
{
    return m_x;
}

double Line::Point::getY() const
{
    return m_y;
}

void Line::Point::setX(double x)
{
    m_x = x;
}

void Line::Point::setY(double y)
{
    m_y = y;
}
