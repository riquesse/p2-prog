#include "chartmanager.h"

ChartManager::ChartManager(QObject *parent)
    : QObject(parent),
      colorGenerator(new ColorGenerator())
{

}

void ChartManager::setModel(Model *model)
{
    m_model = model;
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(dataChanged(QModelIndex)));
    connect(m_model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(headerDataChanged(Qt::Orientation,int,int)));
    connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(rowsRemoved(QModelIndex,int,int)));
    connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(rowsInserted(QModelIndex,int,int)));
    connect(m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(columnsRemoved(QModelIndex,int,int)));
    connect(m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), this, SLOT(columnsInserted(QModelIndex,int,int)));
    connect(m_model, SIGNAL(chartTitleChanged()), this, SLOT(handleChartTitleChanged()));

    initSeries();
}

void ChartManager::setChart(QChart *chart)
{
    m_chart = chart;
    m_chart->setTitle(QString::fromStdString(m_model->getChartTitle()));
    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    m_chart->setTitleFont(font);
}

void ChartManager::handleChartTitleChanged()
{
    m_chart->setTitle(QString::fromStdString(m_model->getChartTitle()));
}
