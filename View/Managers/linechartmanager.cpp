#include "linechartmanager.h"

void LineChartManager::initSeries()
{
    for(int i = 0; i < m_model->rowCount(); ++i){
        CustomLineSeries *lineSeries = new CustomLineSeries();
        lineSeries->setName(m_model->headerData(i, Qt::Vertical).toString());
        lineSeries->setColor(colorGenerator->getRandomColor());
        QPen pen = lineSeries->pen();
        pen.setWidth(3);
        lineSeries->setPen(pen);
        connect(lineSeries, SIGNAL(seriesDoubleClicked(CustomLineSeries*)), this, SLOT(handleSeriesDoubleClicked(CustomLineSeries*)));
        for(int j = 0; j < m_model->columnCount(); ++j) {
            lineSeries->append(j, m_model->data(m_model->index(i, j)).toDouble());
        }

        m_series.append(lineSeries);
    }

    initAxis();
}

void LineChartManager::initAxis()
{
    m_axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    m_axisX->setLabelsAngle(90);
    for(int i = 0; i < m_model->columnCount(); ++i) {
        m_axisX->append(m_model->headerData(i, Qt::Horizontal).toString(),i);
    }

    updateValueAxis();

    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);
    m_axisX->setTitleText(QString::fromStdString(cartesianModel->getAxisXTitle()));
    m_axisY->setTitleText(QString::fromStdString(cartesianModel->getAxisYTitle()));
}

LineChartManager::LineChartManager(QObject *parent)
    : CartesianChartManager(parent),
      m_axisX(new QCategoryAxis()),
      m_axisY(new QValueAxis())
{

}

void LineChartManager::setChart(QChart *chart)
{
    CartesianChartManager::setChart(chart);

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    for(auto it = m_series.begin(); it != m_series.end(); ++it){
        m_chart->addSeries(*it);
        (*it)->attachAxis(m_axisX);
        (*it)->attachAxis(m_axisY);
    }
}

void LineChartManager::columnsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(int i = 0; i < m_model->rowCount(); ++i){
        auto series = m_series.at(i);
        for(int j = first; j <= last; ++j) {
            series->insert(j, QPointF(j, m_model->data(m_model->index(i,j)).toDouble()));
        }
        for(int j = last+1; j < m_model->columnCount(); ++j) {
            series->replace(j, QPointF(j, series->at(j).y()));
        }
    }

    while(m_axisX->count() > first) {
        m_axisX->remove(m_axisX->categoriesLabels().at(first));
    }

    for(int i = first; i < m_model->columnCount(); ++i) {
        m_axisX->append(m_model->headerData(i, Qt::Horizontal).toString(),i);
    }

    if(m_axisX->count() > 1){
        m_axisX->setRange(0, m_axisX->count()-1);
    }
}

void LineChartManager::handleSeriesDoubleClicked(CustomLineSeries *series)
{
    QColorDialog *dialog = new QColorDialog();
    dialog->setOption(QColorDialog::DontUseNativeDialog);
    connect(dialog, &QColorDialog::colorSelected, [=](const QColor& color) {series->setColor(color);});
    dialog->open();
}

void LineChartManager::handleAxisXTitleChanged()
{
    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);

    m_axisX->setTitleText(QString::fromStdString(cartesianModel->getAxisXTitle()));
}

void LineChartManager::handleAxisYTitleChanged()
{
    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);

    m_axisY->setTitleText(QString::fromStdString(cartesianModel->getAxisYTitle()));
}

void LineChartManager::updateValueAxis()
{
    if(m_model->max() == 0 && m_model->min() == m_model->max()){
        m_axisY->setRange(0,50);
    }
    else {
        m_axisY->setRange(m_model->min(), m_model->max());
    }
}

void LineChartManager::columnsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(auto it = m_series.begin(); it != m_series.end(); ++it){
        (*it)->removePoints(first, last-first+1);
        for(int i = first; i < (*it)->count(); ++i) {
            (*it)->replace(i, QPointF(i, (*it)->at(i).y()));
        }
    }

    while(m_axisX->count() > first) {
        m_axisX->remove(m_axisX->categoriesLabels().at(first));
    }

    for(int i = first; i < m_model->columnCount(); ++i) {

        m_axisX->append(m_model->headerData(i, Qt::Horizontal).toString(), i);
    }

    if(m_axisX->count() > 1) {
        m_axisX->setRange(0, m_axisX->count()-1);
    }

    updateValueAxis();
}

void LineChartManager::rowsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(int i = first; i < m_series.size(); ++i){
        m_chart->removeSeries(m_series.at(i));
    }

    for(int i = first; i <= last; ++i){
        CustomLineSeries *lineSeries = new CustomLineSeries();
        lineSeries->setName(m_model->headerData(i, Qt::Vertical).toString());
        lineSeries->setColor(colorGenerator->getRandomColor());
        QPen pen = lineSeries->pen();
        pen.setWidth(3);
        lineSeries->setPen(pen);
        connect(lineSeries, SIGNAL(seriesDoubleClicked(CustomLineSeries*)), this, SLOT(handleSeriesDoubleClicked(CustomLineSeries*)));
        for(int j = 0;  j < m_model->columnCount(); ++j) {
            lineSeries->append(j, m_model->data(m_model->index(i,j)).toDouble());
        }
        m_series.insert(i, lineSeries);
        m_chart->addSeries(lineSeries);
        lineSeries->attachAxis(m_axisX);
        lineSeries->attachAxis(m_axisY);
    }

    for(int i = last +1; i < m_model->rowCount(); ++i) {
        m_chart->addSeries(m_series.at(i));
        m_series.at(i)->attachAxis(m_axisX);
        m_series.at(i)->attachAxis(m_axisY);
    }

    headerDataChanged(Qt::Vertical, last+1, m_model->rowCount()-1);
}

void LineChartManager::rowsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(int i = first; i <= last; ++i) {
        auto series = m_series.takeAt(first);
        m_chart->removeSeries(series);
        delete series;
    }

    emit headerDataChanged(Qt::Vertical, first, m_model->rowCount()-1);

    updateValueAxis();
}

void LineChartManager::headerDataChanged(Qt::Orientation orientation, int first, int last)
{
    switch(orientation) {
        case Qt::Vertical : {
            for(int i = first; i <= last; ++i){
                m_series.at(i)->setName(m_model->headerData(i, orientation).toString());
            }
            break;
        }
        case Qt::Horizontal : {
            for(int i = first; i <= last; ++i) {
                m_axisX->replaceLabel(m_axisX->categoriesLabels().at(i), m_model->headerData(i, orientation).toString());
            }
            break;
        }
    }
}

void LineChartManager::dataChanged(QModelIndex index)
{
    updateValueAxis();

    double value = m_model->data(m_model->index(index.row(), index.column())).toDouble();
    int row = index.row();
    int column = index.column();

    m_series.at(row)->replace(column, QPointF(column, value));
}
