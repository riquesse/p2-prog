#include "customlineseries.h"

CustomLineSeries::CustomLineSeries(QObject *parent) : QLineSeries(parent)
{
    connect(this, SIGNAL(doubleClicked(QPointF)), this, SLOT(onSeriesDoubleClicked()));
}

void CustomLineSeries::onSeriesDoubleClicked()
{
    emit seriesDoubleClicked(this);
}
