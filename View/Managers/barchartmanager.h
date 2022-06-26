#ifndef BARCHARTMANAGER_H
#define BARCHARTMANAGER_H

#include "cartesianchartmanager.h"

class BarChartManager : public CartesianChartManager
{
    Q_OBJECT
private:
    QBarSeries *m_series;
    QBarCategoryAxis *m_axisX;
    QValueAxis *m_axisY;

    void initSeries() override;
    void initAxis() override;
    void updateValueAxis() override;
    
public:
    explicit BarChartManager(QObject *parent = nullptr);
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
    void handleSliceDoubleClicked(int index, QBarSet *barset);
};

#endif // BARCHARTMANAGER_H
