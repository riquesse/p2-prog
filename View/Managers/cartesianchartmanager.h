#ifndef CARTESIANCHARTMANAGER_H
#define CARTESIANCHARTMANAGER_H

#include "chartmanager.h"
#include "Model/Interface/cartesianmodel.h"

class CartesianChartManager : public ChartManager
{
private:
    virtual void initAxis() = 0;
    virtual void updateValueAxis() = 0;

public:
    CartesianChartManager(QObject *parent);
    void setModel(Model *model) override;

private slots:
    virtual void handleAxisXTitleChanged() = 0;
    virtual void handleAxisYTitleChanged() = 0;

};


#endif // CARTESIANCHARTMANAGER_H
