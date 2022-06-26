#ifndef PIECHART_H
#define PIECHART_H

#include "Model/chart.h"
#include "Model/slice.h"

#include <QJsonArray>

class PieChart : public Chart
{
public:
    PieChart(unsigned int slices = 0, unsigned int valuesPerSlice = 0, const std::string& title = "Pie Chart");
    Slice *itemAt(unsigned int index) const override;
    void insert(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // PIECHART_H
