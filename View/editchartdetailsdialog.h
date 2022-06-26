#ifndef EDITCHARTDETAILSDIALOG_H
#define EDITCHARTDETAILSDIALOG_H

#include "Model/Interface/model.h"
#include "Model/Interface/cartesianmodel.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

class EditChartDetailsDialog : public QDialog
{
    Q_OBJECT
private:
    Model *_model;

    QDialogButtonBox *_buttonBox;
    QLineEdit *_chartTitle;
    QLineEdit *_axisXTitle;
    QLineEdit *_axisYTitle;

public:
    explicit EditChartDetailsDialog(Model *model = nullptr, QWidget *parent = nullptr);

signals:
    void changeTitle(const QString& string);
    void changeAxisXTitle(const QString& string);
    void changeAxisYTitle(const QString& string);

public slots:
    void accept() override;
};

#endif // EDITCHARTDETAILSDIALOG_H
