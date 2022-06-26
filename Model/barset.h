#ifndef BARSET_H
#define BARSET_H

#include "chartitem.h"

#include <iostream>
#include <vector>
#include <QJsonArray>
#include <QDebug>

class BarSet : public ChartItem
{
private:
    std::vector<double> m_bars;

    void updateRange() override;

public:
    BarSet(unsigned int bars = 0, const std::string& name = std::string());
    ~BarSet();

    unsigned int count() const override;
    double getValue(unsigned int index) const override;
    void setValue(unsigned int index, double value) override;
    void insert(unsigned int index, unsigned int n) override;
    void remove(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // BARSET_H
