#ifndef CARTESIANCHART_H
#define CARTESIANCHART_H

#include "Model/chart.h"

class CartesianChart : public Chart
{
private:
    std::string m_axisXTitle;
    std::string m_axisYTitle;
public:
    CartesianChart(unsigned int items = 0,
                   const std::string& title = std::string(),
                   const std::string& axisXTitle = std::string(),
                   const std::string& axisYTitle = std::string());

    std::string getAxisXTitle() const;
    std::string getAxisYTitle() const;
    void setAxisXTitle(const std::string& title);
    void setAxisYTitle(const std::string& title);
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // CARTESIANCHART_H
