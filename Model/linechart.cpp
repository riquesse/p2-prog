#include "linechart.h"

LineChart::LineChart(unsigned int lines,
                     unsigned int pointsPerLine,
                     const std::string& title,
                     const std::string& axisXTitle,
                     const std::string& axisYTitle)

    : CartesianChart(lines, title, axisXTitle, axisYTitle)
{
    for(auto it = m_items.begin(); it != m_items.end(); ++it)
        *it = new Line(pointsPerLine);
}

Line *LineChart::itemAt(unsigned int index) const
{
    if(index >= count())
            throw std::out_of_range("PieChart::sliceAt(unsigned int index): index out of range.");

        return dynamic_cast<Line*>(Chart::itemAt(index));
}

void LineChart::insert(unsigned int index, unsigned int n)
{
    if(index > count())
        throw std::out_of_range("LineChart::insertLines(unsigned int index, unsigned int n): index out of range.");

    m_items.insert(m_items.begin()+index, n, new Line(countPerItem()));
}

void LineChart::toJson(QJsonObject &json) const
{
    CartesianChart::toJson(json);

    json["chart-id"] = 2;
    json["lines-number"] = (int) count();
    json["points-per-line"] = (int) countPerItem();

    QJsonArray lines;
    for(auto it = m_items.begin(); it != m_items.end(); ++it){
        QJsonObject line;
        (*it)->toJson(line);
        lines.append(line);
    }

    json["lines"] = lines;
}

void LineChart::fromJson(const QJsonObject &json)
{
    CartesianChart::fromJson(json);

    QJsonArray lines = json["lines"].toArray();
    for(unsigned int i = 0; i < m_items.size(); ++i) {
        m_items.at(i)->fromJson(lines.at(i).toObject());
    }
}
