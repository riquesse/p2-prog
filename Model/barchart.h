#ifndef BARCHART_H
#define BARCHART_H

#include "Model/cartesianchart.h"
#include "Model/barset.h"

#include <QJsonArray>

class BarChart : public CartesianChart
{
public:
    BarChart(unsigned int barSets = 0,
             unsigned int bars = 0,
             const std::string& title = "Bar Chart",
             const std::string& axisXTitle = std::string(),
             const std::string& axisYTitle = std::string());

    BarSet* itemAt(unsigned int index) const override;
    void insert(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // BARCHART_H
