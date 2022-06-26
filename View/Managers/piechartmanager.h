#ifndef PIECHARTMANAGER_H
#define PIECHARTMANAGER_H

#include "chartmanager.h"
#include "Model/Interface/piemodel.h"

class PieChartManager : public ChartManager
{
    Q_OBJECT
private:
    QPieSeries *m_series;

    void initSeries() override;

public:
    PieChartManager(QObject *parent = nullptr);
    void setChart(QChart *chart) override;

private slots:
    void dataChanged(QModelIndex index) override;
    void headerDataChanged(Qt::Orientation orientation, int first, int last) override;
    void rowsRemoved(QModelIndex parent, int first, int last) override;
    void rowsInserted(QModelIndex parent, int first, int last) override;
    void columnsRemoved(QModelIndex parent, int first, int last) override;
    void columnsInserted(QModelIndex parent, int first, int last) override;
    void handleSliceDoubleClicked(QPieSlice *slice);

};

#endif // PIECHARTMANAGER_H
