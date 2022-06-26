#ifndef CUSTOMHEADER_H
#define CUSTOMHEADER_H

#include <QHeaderView>
#include <QLineEdit>

#include <QDebug>

class CustomHeader : public QHeaderView
{
    Q_OBJECT
private:
    QLineEdit *lineEdit;

public:
    explicit CustomHeader(Qt::Orientation orientation, QWidget *parent = nullptr);

signals:

public slots:
    void onSectionDoubleClicked(int section);

};

#endif // CUSTOMHEADER_H
