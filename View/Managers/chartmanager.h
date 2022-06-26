#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <cassert>

#include "Model/Interface/model.h"
#include "Utility/colorgenerator.h"

#include <QObject>
#include <QtCharts>

class ChartManager : public QObject
{
    Q_OBJECT
private:
    virtual void initSeries() = 0;

protected:
    Model *m_model;
    QChart *m_chart;
    ColorGenerator *colorGenerator;

public:
    explicit ChartManager(QObject *parent = nullptr);

    virtual void setModel(Model *model);
    virtual void setChart(QChart *chart);

signals:

private slots:
    void handleChartTitleChanged();

//public slots:
    virtual void dataChanged(QModelIndex index) = 0;
    virtual void headerDataChanged(Qt::Orientation orientation, int first, int last) = 0;
    virtual void rowsRemoved(QModelIndex parent, int first, int last) = 0;
    virtual void rowsInserted(QModelIndex parent, int first, int last) = 0;
    virtual void columnsRemoved(QModelIndex parent, int first, int last) = 0;
    virtual void columnsInserted(QModelIndex parent, int first, int last) = 0;
};

#endif // CHARTMANAGER_H
