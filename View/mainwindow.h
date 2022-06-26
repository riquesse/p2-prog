#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QtCharts>

#include "chartmenu.h"
#include "tableview.h"
#include "Model/Interface/cartesianmodel.h"
#include "Model/Interface/piemodel.h"
#include "Managers/chartmanager.h"
#include "Managers/piechartmanager.h"
#include "Managers/barchartmanager.h"
#include "Managers/linechartmanager.h"
#include "editchartdetailsdialog.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    Model *m_model;
    TableView *m_table;
    QChart *m_chart;
    QChartView *m_chartView;
    ChartManager *m_chartManager;

    QGridLayout *layout;

    QPushButton *_removeButton;
    QPushButton *_insertRowButton;
    QPushButton *_insertColumnButton;
    QPushButton *_saveButton;
    QPushButton *_menuButton;
    QPushButton *_editChartDetailsButton;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void insertRows(int index, int count);

private slots:
    void onInsertRowButtonClicked();
    void onInsertColumnButtonClicked();
    void onRemoveButtonClicked();
    void onSaveButtonClicked();
    void onMenuButtonClicked();
    void onEditChartDetailsButtonClicked();

public slots:
    void initPieChart();
    void initLineChart();
    void initBarChart();
    void parseJson(const QJsonObject& json);

};

#endif // MAINWINDOW_H
