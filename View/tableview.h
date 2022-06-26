#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

#include "customheader.h"

class TableView : public QTableView
{
    Q_OBJECT
private:
    CustomHeader *m_verticalHeader;
    CustomHeader *m_horizontalHeader;
public:
    explicit TableView(QWidget *parent = nullptr);

signals:

public slots:

};

#endif // TABLEVIEW_H
