#include "cartesianmodel.h"

CartesianModel::CartesianModel(QObject *parent) : Model(parent)
{

}

std::string CartesianModel::getAxisXTitle() const
{
    return static_cast<CartesianChart*>(m_chart)->getAxisXTitle();
}

std::string CartesianModel::getAxisYTitle() const
{
    return static_cast<CartesianChart*>(m_chart)->getAxisYTitle();
}

void CartesianModel::setAxisXTitle(const std::string &title)
{
    qDebug() << "CartesianModel::setAxisXTitle";
    static_cast<CartesianChart*>(m_chart)->setAxisXTitle(title);
    emit axisXTitleChanged();
}

void CartesianModel::setAxisYTitle(const std::string &title)
{
    static_cast<CartesianChart*>(m_chart)->setAxisYTitle(title);
    emit axisYTitleChanged();
}

void CartesianModel::setChart(Chart *chart)
{
    if(!dynamic_cast<CartesianChart*>(chart)){
        throw std::invalid_argument("Invalid Chart");

    }
    Model::setChart(chart);
}
