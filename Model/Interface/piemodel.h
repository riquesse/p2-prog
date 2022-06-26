#ifndef PIEMODEL_H
#define PIEMODEL_H

#include "model.h"

class PieModel : public Model
{
    Q_OBJECT
private:
    std::vector<double> m_sliceValues;
public:
    explicit PieModel(QObject *parent = nullptr);
    void setChart(Chart *chart) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeColumns(int column, int count, const QModelIndex &parent) override;
    double getSliceValue(int index) const;
    double min() const override;
    double max() const override;
    void fromJson(const QJsonObject &json) override;
};

#endif // PIEMODEL_H
