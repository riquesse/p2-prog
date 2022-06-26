#include "editchartdetailsdialog.h"

EditChartDetailsDialog::EditChartDetailsDialog(Model *model, QWidget *parent)
    : QDialog(parent),
      _model(model),
      _buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
      _chartTitle(new QLineEdit()),
      _axisXTitle(new QLineEdit()),
      _axisYTitle(new QLineEdit())
{
    setWindowTitle("Modifica dettagli del grafico");
    connect(_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QVBoxLayout *layout = new QVBoxLayout();
    QFormLayout *formLayout = new QFormLayout();
    _chartTitle->setText(QString::fromStdString(_model->getChartTitle()));
    formLayout->addRow(tr("&Titolo grafico:"), _chartTitle);
    CartesianModel *cartesianModel = dynamic_cast<CartesianModel*>(_model);
    if(cartesianModel){
        _axisXTitle->setText(QString::fromStdString(cartesianModel->getAxisXTitle()));
        _axisYTitle->setText(QString::fromStdString(cartesianModel->getAxisYTitle()));
        formLayout->addRow(tr("&Titolo asse x:"), _axisXTitle);
        formLayout->addRow(tr("&Titolo asse y:"), _axisYTitle);
    }
    layout->addLayout(formLayout);
    layout->addWidget(_buttonBox);
    setLayout(layout);
}

void EditChartDetailsDialog::accept()
{
    if(_model){
        CartesianModel *cartesianModel = dynamic_cast<CartesianModel*>(_model);
        if(cartesianModel){
            cartesianModel->setAxisXTitle(_axisXTitle->text().toStdString());
            cartesianModel->setAxisYTitle(_axisYTitle->text().toStdString());
        }
        _model->setChartTitle(_chartTitle->text().toStdString());
    }

    QDialog::accept();
}
