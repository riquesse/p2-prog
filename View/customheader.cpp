#include "customheader.h"

CustomHeader::CustomHeader(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent)
{
    connect(this, SIGNAL(sectionDoubleClicked(int)), this, SLOT(onSectionDoubleClicked(int)));
}

void CustomHeader::onSectionDoubleClicked(int section)
{
    if(model()){
        lineEdit = new QLineEdit(this);
        lineEdit->setText(model()->headerData(section, orientation()).toString());
        lineEdit->selectAll();
        lineEdit->setFocus();
        connect(lineEdit, &QLineEdit::editingFinished, [=]() { model()->setHeaderData(section, orientation(), QVariant(lineEdit->text()));
                                                               lineEdit->close();
                                                               if(orientation() == Qt::Horizontal){
                                                                   QFontMetrics fm(lineEdit->fontMetrics());
                                                                   int width = fm.width(lineEdit->text());
                                                                   resizeSection(section, width+40);
                                                               }
                                                             });
        switch(orientation()) {
            case Qt::Vertical :
                lineEdit->setGeometry(0, sectionViewportPosition(section), size().width(), sectionSize(section));
                break;
            case Qt::Horizontal :
                lineEdit->setGeometry(sectionViewportPosition(section), 0, sectionSize(section), height());
                break;
        }

        lineEdit->show();
    }
}
