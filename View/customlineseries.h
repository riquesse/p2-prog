#ifndef CUSTOMLINESERIES_H
#define CUSTOMLINESERIES_H
#include <QtCharts>

class CustomLineSeries : public QLineSeries
{
    Q_OBJECT
public:
    explicit CustomLineSeries(QObject *parent = nullptr);

signals:
    void seriesDoubleClicked(CustomLineSeries *series);

public slots:
    void onSeriesDoubleClicked();
};

#endif // CUSTOMLINESERIES_H
