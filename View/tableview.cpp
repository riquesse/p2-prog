#include "tableview.h"

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_verticalHeader(new CustomHeader(Qt::Vertical, this)),
      m_horizontalHeader(new CustomHeader(Qt::Horizontal, this))
{
    m_verticalHeader->setSectionsClickable(true);
    setVerticalHeader(m_verticalHeader);
    m_horizontalHeader->setSectionsClickable(true);
    setHorizontalHeader(m_horizontalHeader);
}
