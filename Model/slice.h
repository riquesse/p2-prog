#ifndef SLICE_H
#define SLICE_H

#include "chartitem.h"

#include <iostream>
#include <vector>

#include <QDebug>
#include <QJsonArray>

class Slice : public ChartItem
{
private:
    std::vector<double> m_values;

    void updateRange() override;

public:
    Slice(unsigned int valuesPerSlice = 0, const std::string& name = std::string());

    unsigned int count() const override;
    double getValue(unsigned int index) const override;
    void setValue(unsigned int index, double value) override;
    void insert(unsigned int index, unsigned int n) override;
    void remove(unsigned int index, unsigned int n) override;
    void toJson(QJsonObject &json) const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // SLICE_H
