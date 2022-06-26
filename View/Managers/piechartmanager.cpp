#include "piechartmanager.h"

void PieChartManager::initSeries()
{
    for(int i=0; i<m_model->rowCount(); ++i){
        QString header = m_model->headerData(i, Qt::Vertical).toString();
        double data = static_cast<PieModel*>(m_model)->getSliceValue(i);

        QPieSlice *slice = new QPieSlice(header, data);
        slice->setColor(colorGenerator->getRandomColor());
        m_series->append(slice);
    }
}

PieChartManager::PieChartManager(QObject *parent)
    : ChartManager(parent),
      m_series(new QPieSeries(this))
{
    connect(m_series, SIGNAL(doubleClicked(QPieSlice*)), this, SLOT(handleSliceDoubleClicked(QPieSlice*)));
}

void PieChartManager::setChart(QChart *chart)
{
    ChartManager::setChart(chart);
    m_chart->addSeries(m_series);
}

void PieChartManager::dataChanged(QModelIndex index)
{
    auto slice = m_series->slices().at(index.row());
    double value = static_cast<PieModel*>(m_model)->getSliceValue(index.row());
    value <= 0 ? slice->setValue(0) : slice->setValue(value);

    if(m_model->max() <= 0 && m_model->min() <= 0){    //[1]
        m_chart->removeSeries(m_series);
        auto slice = m_series->slices().at(index.row());
        QPieSlice *newSlice = new QPieSlice(slice->label(), slice->value());
        newSlice->setColor(slice->color());
        m_series->remove(slice);
        m_series->insert(index.row(), newSlice);
        m_chart->addSeries(m_series);
    }
}

void PieChartManager::headerDataChanged(Qt::Orientation orientation, int first, int last)
{
    if(orientation == Qt::Vertical) {
        auto slices = m_series->slices();
        for(int i = first; i <= last; ++i) {
            slices.at(i)->setLabel(m_model->headerData(i, orientation).toString());
        }
    }
}

void PieChartManager::rowsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    auto slices = m_series->slices();
    for(int i = first; i <= last; ++i){
        m_series->remove(slices.at(i));
    }

    emit headerDataChanged(Qt::Vertical, first, m_model->rowCount()-1);
}

void PieChartManager::rowsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    m_chart->removeSeries(m_series);

    for(int i = first; i <= last; ++i) {
        QPieSlice *slice = new QPieSlice();
        double value = static_cast<PieModel*>(m_model)->getSliceValue(i);
        slice->setValue(value);
        slice->setColor(colorGenerator->getRandomColor());
        m_series->insert(i, slice);
    }

    emit headerDataChanged(Qt::Vertical, first, m_model->rowCount()-1);

    m_chart->addSeries(m_series);
}

void PieChartManager::columnsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    auto slices = m_series->slices();
    for(int i = 0;  i < m_model->rowCount(); ++i) {
        double value = static_cast<PieModel*>(m_model)->getSliceValue(i);
        slices.at(i)->setValue(value <= 0 ? 0 : value);
    }
}

void PieChartManager::columnsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    auto slices = m_series->slices();
    for(int i = 0;  i < m_model->rowCount(); ++i) {
        double value = static_cast<PieModel*>(m_model)->getSliceValue(i);;
        slices.at(i)->setValue(value <= 0 ? 0 : value);
    }
}

void PieChartManager::handleSliceDoubleClicked(QPieSlice *slice)
{
    QColorDialog *dialog = new QColorDialog();
    dialog->setOption(QColorDialog::DontUseNativeDialog);
    connect(dialog, &QColorDialog::colorSelected, [=](const QColor& color) { slice->setColor(color); });
    dialog->open();
}

/*
 * [1] bug Qt: dopo aver inizializzato le varie slice con valori > 0, nel caso i valori vengano settati a 0 una slice rimane visibile
 */
