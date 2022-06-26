#include "barchartmanager.h"

void BarChartManager::initSeries()
{
    for(int i = 0; i < m_model->rowCount(); ++i){
        QBarSet *barSet = new QBarSet(m_model->headerData(i, Qt::Vertical).toString());
        barSet->setColor(colorGenerator->getRandomColor());
        for(int j = 0; j < m_model->columnCount(); ++j) {
            barSet->append(m_model->data(m_model->index(i, j)).toDouble());
        }

        m_series->append(barSet);
    }

    initAxis();
}

void BarChartManager::updateValueAxis()
{
    if(m_model->max() == 0 && m_model->min() == m_model->max()) {
        m_axisY->setRange(0,50);
    }
    else{
        m_axisY->setRange(m_model->min(), m_model->max());
    }
}

void BarChartManager::initAxis()
{
    for(int i = 0; i < m_model->columnCount(); ++i) {
        m_axisX->append(m_model->headerData(i, Qt::Horizontal).toString());
    }

    updateValueAxis();

    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);
    m_axisX->setTitleText(QString::fromStdString(cartesianModel->getAxisXTitle()));
    m_axisY->setTitleText(QString::fromStdString(cartesianModel->getAxisYTitle()));
}

BarChartManager::BarChartManager(QObject *parent)
    : CartesianChartManager(parent),
      m_series(new QBarSeries(this)),
      m_axisX(new QBarCategoryAxis(this)),
      m_axisY(new QValueAxis(this))
{
    connect(m_series, SIGNAL(doubleClicked(int,QBarSet*)), this, SLOT(handleSliceDoubleClicked(int,QBarSet*)));
}

void BarChartManager::setChart(QChart *chart)
{
    CartesianChartManager::setChart(chart);

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);
    m_chart->addSeries(m_series);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
}

void BarChartManager::dataChanged(QModelIndex index)
{
    updateValueAxis();

    auto barSet = m_series->barSets().at(index.row());
    barSet->replace(index.column(), m_model->data(m_model->index(index.row(), index.column())).toDouble());
}

void BarChartManager::headerDataChanged(Qt::Orientation orientation, int first, int last)
{
    switch(orientation) {
        case Qt::Horizontal : {
            for(int i = first; i <= last; ++i){
                m_axisX->replace(m_axisX->categories().at(i), m_model->headerData(i, orientation).toString());
            }
            break;
        }
        case Qt::Vertical : {
            for(int i = first; i <= last; ++i){
                m_series->barSets().at(i)->setLabel(m_model->headerData(i, orientation).toString());
            }
            break;
        }
    }
}

void BarChartManager::rowsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(int i = first; i <= last; ++i) {
        m_series->remove(m_series->barSets().at(first));
    }

    headerDataChanged(Qt::Vertical, first, m_model->rowCount()-1);

    updateValueAxis();
}

void BarChartManager::rowsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    m_chart->removeSeries(m_series);

    for(int i = first; i <= last; ++i) {
        QBarSet *barSet = new QBarSet(m_model->headerData(i, Qt::Vertical).toString());
        barSet->setColor(colorGenerator->getRandomColor());
        for(int j = 0; j < m_model->columnCount(); ++j) {
            barSet->append(m_model->data(m_model->index(i,j)).toDouble());
        }

        m_series->insert(i, barSet);
    }

    emit headerDataChanged(Qt::Vertical, last+1, m_model->rowCount()-1);

    m_chart->addSeries(m_series);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
}

void BarChartManager::columnsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    for(int i = 0; i < m_model->rowCount(); ++i){
        m_series->barSets().at(i)->remove(first, last-first+1);
    }

    for(int i = first;  i <= last; ++i){
        m_axisX->remove(m_axisX->categories().at(first));
    }

    emit headerDataChanged(Qt::Horizontal, first, m_model->columnCount()-1);

    updateValueAxis();

    if(m_axisX->count() > 0)
        m_axisX->setRange(m_axisX->categories().at(0), m_axisX->categories().at(m_axisX->count()-1));
    else{
        m_chart->removeAxis(m_axisX);
        m_chart->addAxis(m_axisX, Qt::AlignBottom);
        m_series->attachAxis(m_axisX);
    }
}

void BarChartManager::columnsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);

    emit headerDataChanged(Qt::Horizontal, first, m_axisX->count()-1);

    for(int i = first; i <= last; ++i){
        m_axisX->append(m_model->headerData(m_axisX->count(), Qt::Horizontal).toString());
        for(int j = 0; j < m_model->rowCount(); ++j){
            m_series->barSets().at(j)->insert(i, m_model->data(m_model->index(j,i)).toDouble());
        }
    }

    m_axisX->setRange(m_axisX->categories().at(0), m_axisX->categories().at(m_axisX->count()-1));
}

void BarChartManager::handleSliceDoubleClicked(int index, QBarSet *barset)
{
    Q_UNUSED(index);

    QColorDialog *dialog = new QColorDialog();
    dialog->setOption(QColorDialog::DontUseNativeDialog);
    connect(dialog, &QColorDialog::colorSelected, [=](const QColor& color) { barset->setColor(color); });
    dialog->open();
}

void BarChartManager::handleAxisXTitleChanged()
{
    qDebug() << "entra qui";
    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);

    m_axisX->setTitleText(QString::fromStdString(cartesianModel->getAxisXTitle()));
    qDebug() << m_axisX->titleText();
}

void BarChartManager::handleAxisYTitleChanged()
{
    CartesianModel *cartesianModel = static_cast<CartesianModel*>(m_model);

    m_axisY->setTitleText(QString::fromStdString(cartesianModel->getAxisYTitle()));
}
