#include "cartesianchartmanager.h"

CartesianChartManager::CartesianChartManager(QObject *parent)
    : ChartManager(parent)
{

}

void CartesianChartManager::setModel(Model *model)
{
    CartesianModel *cartesianModel = static_cast<CartesianModel*>(model);
    connect(cartesianModel, SIGNAL(axisXTitleChanged()), this, SLOT(handleAxisXTitleChanged()));
    connect(cartesianModel, SIGNAL(axisYTitleChanged()), this, SLOT(handleAxisYTitleChanged()));

    ChartManager::setModel(model);
}
