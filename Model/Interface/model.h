#ifndef MODEL_H
#define MODEL_H

#include "Model/chart.h"
#include "Model/piechart.h"
#include "Model/cartesianchart.h"
#include "Model/barchart.h"
#include "Model/linechart.h"

#include <cassert>
#include <QAbstractTableModel>

class Model : public QAbstractTableModel
{
    Q_OBJECT
protected:
    Chart *m_chart;
    std::vector<std::string> m_categories;

public:
    Model(QObject *parent = nullptr);
    virtual ~Model();

    Chart *getChart() const;
    virtual void setChart(Chart *chart);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    void toJson(QJsonObject& json) const;
    virtual void fromJson(const QJsonObject& json);
    virtual double min() const;
    virtual double max() const;
    std::string getChartTitle() const;
    void setChartTitle(const std::string& title);

signals:
    void chartTitleChanged();
};

#endif // MODEL_H
