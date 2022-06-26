#include "model.h"

#include <QDebug>

Model::Model(QObject *parent)
    : QAbstractTableModel(parent)
{
}

Model::~Model()
{
    delete m_chart;
}

Chart *Model::getChart() const
{
    return m_chart;
}

void Model::setChart(Chart *chart)
{
    m_chart = chart;
    m_categories = std::vector<std::string>(columnCount(), std::string());
}

int Model::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_chart->count();

    return 0;
}

int Model::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_chart->countPerItem();

    return 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole :
        case Qt::EditRole : {
            return m_chart->itemAt(index.row())->getValue(index.column());
        }
        default :
            return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    m_chart->itemAt(index.row())->setValue(index.column(), value.toDouble());
    emit dataChanged(index, index);
    return true;
}

bool Model::insertRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(row > rowCount())
        return false;

    beginInsertRows(parent, row, row+count-1);
    m_chart->insert(row, count);
    endInsertRows();
    return true;
}

bool Model::insertColumns(int column, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(column > columnCount())
        return false;

    beginInsertColumns(parent, column, column+count-1);
    for(unsigned int i=0; i<m_chart->count(); ++i){
        m_chart->itemAt(i)->insert(column, count);
    }

    m_categories.insert(m_categories.begin()+column, count, std::string());

    endInsertColumns();
    return true;
}

bool Model::removeRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(row + count > rowCount())
        return false;

    beginRemoveRows(parent, row, row+count-1);
    m_chart->remove(row, count);
    endRemoveRows();
    return true;
}

bool Model::removeColumns(int column, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(column + count > columnCount())
        return false;

    beginRemoveColumns(parent, column, column+count-1);

    for(unsigned int i=0; i<m_chart->count(); ++i){
        m_chart->itemAt(i)->remove(column, count);
    }
    m_categories.erase(m_categories.begin()+column, m_categories.begin()+column+count);

    endRemoveColumns();
    return true;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        switch(orientation) {
            case Qt::Horizontal : {
                auto label = m_categories[section];
                return label != std::string() ? QVariant(QString::fromStdString(label)) : QVariant(section);
            }
            case Qt::Vertical : {
                auto label = m_chart->itemAt(section)->getName();
                return label != std::string() ? QVariant(QString::fromStdString(label)) : QVariant(section);
            }
            default : return QVariant();
        }
    }
    return QVariant();
}

bool Model::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        switch(orientation) {
            case Qt::Horizontal : {
                if(section >= columnCount())
                    return false;

                m_categories[section] = value.toString().toStdString();
                emit headerDataChanged(Qt::Horizontal, section, section);
                return true;
            }
            case Qt::Vertical : {
                if(section >= rowCount())
                    return false;

                m_chart->itemAt(section)->setName(value.toString().toStdString());
                emit headerDataChanged(Qt::Vertical, section, section);
                return true;
            }

            default : return false;
        }
    }
    return false;
}

void Model::toJson(QJsonObject &json) const
{
    QJsonArray categories;
    for(auto it = m_categories.begin(); it != m_categories.end(); ++it){
        categories.append(QString::fromStdString(*it));
    }

    json["categories"] = categories;

    m_chart->toJson(json);
}

void Model::fromJson(const QJsonObject &json)
{
    QJsonArray categories = json["categories"].toArray();
    for(unsigned int i = 0; i < m_categories.size(); ++i){
        m_categories[i] = categories.at(i).toString().toStdString();
    }

    m_chart->fromJson(json);
}

double Model::min() const
{
    return m_chart->min();
}

double Model::max() const
{
    return m_chart->max();
}

std::string Model::getChartTitle() const
{
    return m_chart->getTitle();
}

void Model::setChartTitle(const std::string &title)
{
    m_chart->setTitle(title);
    emit chartTitleChanged();
}
