#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <string>
#include <vector>
#include <QJsonObject>

class ChartItem
{
private:
    std::string m_name;

    virtual void updateRange() = 0;

protected:
    double m_min, m_max;

public:
    ChartItem(const std::string & name);
    virtual ~ChartItem() = default;


    virtual double getValue(unsigned int index) const = 0;
    virtual void setValue(unsigned int index, double value) = 0;
    std::string getName() const;
    void setName(const std::string& name);
    virtual void insert(unsigned int index, unsigned int n) = 0;
    virtual void remove(unsigned int index, unsigned int n) = 0;
    virtual unsigned int count() const = 0;
    virtual void toJson(QJsonObject& json) const = 0;
    virtual void fromJson(const QJsonObject& json) = 0;

    double min() const;
    double max() const;
};

#endif // CHARTITEM_H
