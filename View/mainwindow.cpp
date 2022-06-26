#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();

    QVBoxLayout *vLayout = new QVBoxLayout();
    QGridLayout *buttonsLayout = new QGridLayout();
    _removeButton = new QPushButton();
    _removeButton->setToolTip("Rimuovi una selezione di righe e/o colonne");
    _removeButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _removeButton->setIcon(QIcon(":/Icons/res/clear.png"));
    _removeButton->setIconSize(QSize(50,50));
    connect(_removeButton, SIGNAL(clicked(bool)), this, SLOT(onRemoveButtonClicked()));
    buttonsLayout->addWidget(_removeButton, 0, 0);

    _insertColumnButton = new QPushButton();
    _insertColumnButton->setToolTip("Inserisci una nuova colonna");
    _insertColumnButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _insertColumnButton->setIcon(QIcon(":/Icons/res/insertcolumnicon.png"));
    _insertColumnButton->setIconSize(QSize(50,50));
    connect(_insertColumnButton, SIGNAL(clicked(bool)), this, SLOT(onInsertColumnButtonClicked()));
    buttonsLayout->addWidget(_insertColumnButton, 0, 1);

    _insertRowButton = new QPushButton();
    _insertRowButton->setToolTip("Inserisci una nuova riga");
    _insertRowButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _insertRowButton->setIcon(QIcon(":/Icons/res/insertrowicon.png"));
    _insertRowButton->setIconSize(QSize(50,50));
    connect(_insertRowButton, SIGNAL(clicked(bool)), this, SLOT(onInsertRowButtonClicked()));
    buttonsLayout->addWidget(_insertRowButton, 0, 2);

    _saveButton = new QPushButton();
    _saveButton->setToolTip("Salva su file");
    _saveButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _saveButton->setIcon(QIcon(":/Icons/res/save.png"));
    _saveButton->setIconSize(QSize(50,50));
    connect(_saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    buttonsLayout->addWidget(_saveButton, 1, 0);

    _menuButton = new QPushButton();
    _menuButton->setToolTip("Torna al menu principale");
    _menuButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _menuButton->setIcon(QIcon(":/Icons/res/menu.png"));
    _menuButton->setIconSize(QSize(50,50));
    connect(_menuButton, SIGNAL(clicked(bool)), this, SLOT(onMenuButtonClicked()));
    buttonsLayout->addWidget(_menuButton, 1, 1);

    _editChartDetailsButton = new QPushButton();
    _editChartDetailsButton->setToolTip("Modifica dettagli grafico");
    _editChartDetailsButton->setStyleSheet(("padding: 0.3em; background-color:#ACE7FB;"));
    _editChartDetailsButton->setIcon(QIcon(":/Icons/res/edit.png"));
    _editChartDetailsButton->setIconSize(QSize(50,50));
    connect(_editChartDetailsButton, SIGNAL(clicked(bool)), this, SLOT(onEditChartDetailsButtonClicked()));
    buttonsLayout->addWidget(_editChartDetailsButton, 1, 2);

    m_table = new TableView(this);
    m_table->setMaximumWidth(500);
    vLayout->addWidget(m_table);
    vLayout->addLayout(buttonsLayout);
    layout->addLayout(vLayout);

    m_chart = new QChart();
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->layout()->setContentsMargins(4,4,4,4);

    m_chartView = new QChartView();
    m_chartView->setRenderHint(QPainter::Antialiasing);
    QBrush brush(QColor("#ACE7FB"));
    m_chartView->setBackgroundBrush(brush);

    layout->addWidget(m_chartView);

    setLayout(layout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onInsertRowButtonClicked()
{
    QModelIndexList selectedRows = m_table->selectionModel()->selectedRows();
    if(selectedRows.empty()) {
        m_model->insertRows(m_model->rowCount(), 1);
    }
    else{
        m_model->insertRows(selectedRows.begin()->row(), 1);
    }

    if(m_model->columnCount() == 0)
        m_model->insertColumns(m_model->columnCount(), 1);
}

void MainWindow::onInsertColumnButtonClicked()
{
    if(m_model->rowCount() == 0) {
        m_model->insertRows(m_model->rowCount(), 1);
    }

    QModelIndexList selectedColumns = m_table->selectionModel()->selectedColumns();
    if(selectedColumns.empty()) {
        m_model->insertColumns(m_model->columnCount(), 1);
    }
    else {
        m_model->insertColumns(selectedColumns.begin()->column(), 1);
    }
}

void MainWindow::onRemoveButtonClicked()
{
    QModelIndexList selectedRows = m_table->selectionModel()->selectedRows();
    std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex& a, const QModelIndex& b) { return b < a; });
    QModelIndexList selectedColumns = m_table->selectionModel()->selectedColumns();
    std::sort(selectedColumns.begin(), selectedColumns.end(), [](const QModelIndex& a, const QModelIndex& b) { return b < a; });

    for(auto it = selectedColumns.begin(); it != selectedColumns.end(); ++it) {
        m_model->removeColumns(it->column(), 1);
    }

    for(auto it = selectedRows.begin(); it != selectedRows.end(); ++it) {
        m_model->removeRows(it->row(), 1);
    }
}

void MainWindow::onSaveButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QString(), "*.json", nullptr, QFileDialog::DontUseNativeDialog);
    if(fileName == QString()){
        QMessageBox msgBox(this);
        msgBox.setText("Nessun file selezionato.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else{
        QFile saveFile(fileName);
        if(!saveFile.open(QIODevice::WriteOnly)){
            QMessageBox msgBox(this);
            msgBox.setText("Non è possibile aprire il file selezionato.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
        else{
            QJsonObject json;
            m_model->toJson(json);
            saveFile.write(QJsonDocument(json).toJson());
        }
    }
}

void MainWindow::onMenuButtonClicked()
{
    ChartMenu *menu = new ChartMenu();
    menu->show();
    close();
}

void MainWindow::onEditChartDetailsButtonClicked()
{
    EditChartDetailsDialog *dialog = new EditChartDetailsDialog(m_model, this);
    dialog->exec();
}

void MainWindow::initPieChart()
{
    m_model = new PieModel(this);
    m_model->setChart(new PieChart(3,3));

    m_table->setModel(m_model);

    m_chartManager = new PieChartManager(this);
    m_chartManager->setModel(m_model);
    m_chartManager->setChart(m_chart);

    m_chartView->setChart(m_chart);

}

void MainWindow::initLineChart()
{
    m_model = new CartesianModel(this);
    m_model->setChart(new LineChart(3,3));

    m_table->setModel(m_model);

    m_chartManager = new LineChartManager(this);
    m_chartManager->setModel(m_model);
    m_chartManager->setChart(m_chart);

    m_chartView->setChart(m_chart);

}

void MainWindow::initBarChart()
{
    m_model = new CartesianModel(this);
    m_model->setChart(new BarChart(3,3));

    m_table->setModel(m_model);

    m_chartManager = new BarChartManager(this);
    m_chartManager->setModel(m_model);
    m_chartManager->setChart(m_chart);

    m_chartView->setChart(m_chart);

}

void MainWindow::parseJson(const QJsonObject &json)
{
    int chartID = json["chart-id"].toInt();
    switch(chartID) {
        case 0: {
            int slices = json["slices-number"].toInt();
            int valuesPerSlice = json["values-per-slice"].toInt();
            m_model = new PieModel(this);
            m_model->setChart(new PieChart(slices, valuesPerSlice));
            m_model->fromJson(json);

            m_table->setModel(m_model);

            m_chartManager = new PieChartManager(this);
            m_chartManager->setModel(m_model);
            m_chartManager->setChart(m_chart);

            m_chartView->setChart(m_chart);
            break;
        }
        case 1: {
            int barsets = json["barsets-number"].toInt();
            int bars = json["bars-number"].toInt();
            m_model = new CartesianModel(this);
            m_model->setChart(new BarChart(barsets, bars));
            m_model->fromJson(json);

            m_table->setModel(m_model);

            m_chartManager = new BarChartManager(this);
            m_chartManager->setModel(m_model);
            m_chartManager->setChart(m_chart);

            m_chartView->setChart(m_chart);
            break;
        }
        case 2: {
            int lines = json["lines-number"].toInt();
            int pointsPerLine = json["points-per-line"].toInt();
            m_model = new CartesianModel(this);
            m_model->setChart(new LineChart(lines, pointsPerLine));
            m_model->fromJson(json);

            m_table->setModel(m_model);

            m_chartManager = new LineChartManager(this);
            m_chartManager->setModel(m_model);
            m_chartManager->setChart(m_chart);

            m_chartView->setChart(m_chart);

            break;
        }
    }
}
