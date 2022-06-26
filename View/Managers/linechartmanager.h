#ifndef LINECHARTMANAGER_H
#define LINECHARTMANAGER_H

#include "cartesianchartmanager.h"
#include "View/customlineseries.h"

class LineChartManager : public CartesianChartManager
{
    Q_OBJECT
private:
    QList<CustomLineSeries*> m_series;
    QCategoryAxis *m_axisX;
    QValueAxis *m_axisY;

    void initSeries() override;
    void initAxis() override;
    void updateValueAxis() override;
    
public:
    explicit LineChartManager(QObject *parent = nullptr);
    void setChart(QChart *chart) override;

private slots:
    void handleAxisXTitleChanged() override;
    void handleAxisYTitleChanged() override;
    void dataChanged(QModelIndex index) override;
    void headerDataChanged(Qt::Orientation orientation, int first, int last) override;
    void rowsRemoved(QModelIndex parent, int first, int last) override;
    void rowsInserted(QModelIndex parent, int first, int last) override;
    void columnsRemoved(QModelIndex parent, int first, int last) override;
    void columnsInserted(QModelIndex parent, int first, int last) override;
    void handleSeriesDoubleClicked(CustomLineSeries *series);
};

#endif // LINECHARTMANAGER_H
