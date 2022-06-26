#ifndef LINECHART_H
#define LINECHART_H

#include "Model/cartesianchart.h"
#include "Model/line.h"

#include <QJsonArray>

class LineChart : public CartesianChart
{
public:
    LineChart(unsigned int lines = 0,
              unsigned int pointsPerLine = 0,
              const std::string& title = "Line Chart",
              const std::string& axisXTitle = std::string(),
              const std::string& axisYTitle = std::string());

    Line* itemAt(unsigned int index) const override;
    void insert(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // LINECHART_H
