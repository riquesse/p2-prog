#include "chartmenu.h"

#include <QGridLayout>
#include <cmath>

void ChartMenu::onPieChartButtonClicked()
{
    accept();
    MainWindow *mainWindow = new MainWindow();
    connect(this, SIGNAL(createPieChart()), mainWindow, SLOT(initPieChart()));
    emit createPieChart();
    mainWindow->showMaximized();
}

void ChartMenu::onLineChartButtonClicked()
{
    accept();
    MainWindow *mainWindow = new MainWindow();
    connect(this, SIGNAL(createLineChart()), mainWindow, SLOT(initLineChart()));
    emit createLineChart();
    mainWindow->showMaximized();
}

void ChartMenu::onBarChartButtonClicked()
{
    accept();
    MainWindow *mainWindow = new MainWindow();
    connect(this, SIGNAL(createBarChart()), mainWindow, SLOT(initBarChart()));
    emit createBarChart();
    mainWindow->showMaximized();
}

void ChartMenu::onImportButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", QString(), "*.json", nullptr, QFileDialog::DontUseNativeDialog);
    if(fileName == QString()) {
        QMessageBox msgBox(this);
        msgBox.setText("Nessun file selezionato.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else{
    QFile loadFile(fileName);
        if (!loadFile.open(QIODevice::ReadOnly)) {
            QMessageBox msgBox(this);
            msgBox.setText("Non è possibile aprire il file selezionato.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
        else{
            const QByteArray saveData = loadFile.readAll();
            const QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
            const QJsonObject json = loadDoc.object();

            if(JsonChecker::isValid(json)){
                accept();
                MainWindow *mainWindow = new MainWindow();
                connect(this, SIGNAL(parseJson(QJsonObject)), mainWindow, SLOT(parseJson(QJsonObject)));
                emit parseJson(json);
                mainWindow->showMaximized();
            }
            else{
                QMessageBox msgBox(this);
                msgBox.setText("Il file selezionato non è valido.");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
            }
        }
    }
}

ChartMenu::ChartMenu(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("QuteCharts");

    _pieChart = new QPushButton(this);
    _pieChart->setToolTip("Create a new Pie Chart");
    _pieChart->setIcon(QIcon(":/Icons/res/pie-chart.png"));
    _pieChart->setIconSize(QSize(120, 120));
    connect(_pieChart, SIGNAL(clicked(bool)), this, SLOT(onPieChartButtonClicked()));

    _lineChart = new QPushButton(this);
    _lineChart->setToolTip("Create a new Line Chart");
    _lineChart->setIcon(QIcon(":/Icons/res/line-chart.png"));
    _lineChart->setIconSize(QSize(120, 120));
    connect(_lineChart, SIGNAL(clicked(bool)), this, SLOT(onLineChartButtonClicked()));

    _barChart = new QPushButton(this);
    _barChart->setToolTip("Create a new Bar Chart");
    _barChart->setIcon(QIcon(":/Icons/res/bar-chart.png"));
    _barChart->setIconSize(QSize(120, 120));
    connect(_barChart, SIGNAL(clicked(bool)), this, SLOT(onBarChartButtonClicked()));

    _importChart = new QPushButton(this);
    _importChart->setToolTip("Open a Chart");
    _importChart->setIcon(QIcon(":/Icons/res/open.png"));
    _importChart->setIconSize(QSize(120,120));
    connect(_importChart, SIGNAL(clicked(bool)), this, SLOT(onImportButtonClicked()));

    _label = new QLabel(this);
    QPixmap pix(":/Icons/res/logo.png");
    _label->setPixmap(pix);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(_label, 0, 0, 1, 4, Qt::AlignCenter);
    layout->addWidget(_pieChart, 1, 0);
    layout->addWidget(_lineChart, 1, 1);
    layout->addWidget(_barChart, 1, 2);
    layout->addWidget(_importChart, 1, 3);

    setLayout(layout);
}
