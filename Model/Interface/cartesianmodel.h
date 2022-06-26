#ifndef CARTESIANMODEL_H
#define CARTESIANMODEL_H

#include "model.h"

class CartesianModel : public Model
{
    Q_OBJECT

public:
    explicit CartesianModel(QObject *parent = nullptr); //aggiungere Chart* e lanciare eccezione se non è <= CartesianChart
    std::string getAxisXTitle() const;
    std::string getAxisYTitle() const;
    void setAxisXTitle(const std::string& title);
    void setAxisYTitle(const std::string& title);
    void setChart(Chart *chart) override;

signals:
    void axisXTitleChanged();
    void axisYTitleChanged();
};

#endif // CARTESIANMODEL_H
