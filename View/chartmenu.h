#ifndef CHARTMENU_H
#define CHARTMENU_H

#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "mainwindow.h"
#include "Utility/jsonchecker.h"

#include <QDebug>

class ChartMenu : public QDialog
{
    Q_OBJECT
private:
    QPushButton *_pieChart;
    QPushButton *_lineChart;
    QPushButton *_barChart;
    QPushButton *_importChart;
    QLabel *_label;

private slots:
    void onPieChartButtonClicked();
    void onLineChartButtonClicked();
    void onBarChartButtonClicked();
    void onImportButtonClicked();

public:
    explicit ChartMenu(QWidget *parent = nullptr);
    ~ChartMenu() = default;

signals:
    void createPieChart();
    void createLineChart();
    void createBarChart();
    void parseJson(const QJsonObject& json);

public slots:

};

#endif // CHARTMENU_H
