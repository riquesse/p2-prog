#ifndef CHART_H
#define CHART_H

#include "Model/chartitem.h"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <QJsonObject>

#include <QDebug>

class Chart
{
protected:
    std::vector<ChartItem*> m_items;
    std::string m_title;

public:
    Chart(unsigned int items = 0, const std::string& title = std::string());
    virtual ~Chart();
    Chart(const Chart& chart);
    Chart& operator=(const Chart& chart);
    unsigned int count() const;
    unsigned int countPerItem() const;
    virtual void insert(unsigned int index, unsigned int n) = 0;
    void remove(unsigned int index, unsigned int n);
    virtual ChartItem *itemAt(unsigned int index) const = 0;
    void setTitle(const std::string& title);
    std::string getTitle() const;
    virtual void toJson(QJsonObject& json) const;
    virtual void fromJson(const QJsonObject& json);

    double min() const;
    double max() const;
};

#endif // CHART_H
