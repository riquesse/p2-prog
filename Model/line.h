#ifndef LINE_H
#define LINE_H

#include "chartitem.h"

#include <vector>
#include <iostream>
#include <stdexcept>

#include <QJsonArray>

class Line : public ChartItem
{
private:
    class Point
    {
    private:
        double m_x, m_y;

    public:
        Point(double x = 0, double y = 0);
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
    };

    std::vector<Point> m_points;

    void updateRange() override;

public:
    Line(unsigned int pointsPerLine = 0, const std::string& name = std::string());

    unsigned int count() const override;
    double getX(unsigned int index) const;
    double getY(unsigned int index) const;
    void setX(unsigned int index, double value);
    void setY(unsigned int index, double value);
    double getValue(unsigned int index) const override;
    void setValue(unsigned int index, double value) override;
    void insert(unsigned int index, unsigned int n) override;
    void remove(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // LINE_H
