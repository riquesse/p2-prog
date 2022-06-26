#include "piemodel.h"

PieModel::PieModel(QObject *parent)
    : Model(parent)
{

}

void PieModel::setChart(Chart *chart)
{
    if(!dynamic_cast<PieChart*>(chart)){
        throw std::invalid_argument("Invalid Chart");
    }

    Model::setChart(chart);

    for(int row = 0; row < rowCount(); ++row){
        double sliceValue = 0;
        for(int column = 0; column < columnCount(); ++column){
            sliceValue += m_chart->itemAt(row)->getValue(column);
        }
        m_sliceValues.push_back(sliceValue);
    }
}

bool PieModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(row + count > rowCount())
        return false;

    beginRemoveRows(parent, row, row+count-1);
    m_chart->remove(row, count);
    auto first = m_sliceValues.begin()+row;
    auto last = first + count;
    m_sliceValues.erase(first, last);
    endRemoveRows();
    return true;
}

bool PieModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    double toSubtract = m_chart->itemAt(index.row())->getValue(index.column());
    double toAdd = value.toDouble();

    m_sliceValues[index.row()] = m_sliceValues[index.row()] - toSubtract + toAdd;

    m_chart->itemAt(index.row())->setValue(index.column(), value.toDouble());
    emit dataChanged(index, index);
    return true;
}

bool PieModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(row > rowCount())
        return false;

    beginInsertRows(parent, row, row+count-1);
    m_chart->insert(row, count);
    m_sliceValues.insert(m_sliceValues.begin()+row, count, 0);
    endInsertRows();
    return true;
}

bool PieModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    if(parent.isValid())
        return false;

    if(column + count > columnCount())
        return false;

    beginRemoveColumns(parent, column, column+count-1);

    for(int row = 0; row < rowCount(); ++row) {
        for(int col = column; col < column+count; ++col) {
            m_sliceValues[row] -= m_chart->itemAt(row)->getValue(col);
        }
    }

    for(unsigned int i=0; i<m_chart->count(); ++i){
        m_chart->itemAt(i)->remove(column, count);
    }

    m_categories.erase(m_categories.begin()+column, m_categories.begin()+column+count);

    endRemoveColumns();
    return true;
}

double PieModel::getSliceValue(int index) const
{
    return m_sliceValues[index];
}

double PieModel::min() const
{
    double min;
    bool init = false;
    for(auto it = m_sliceValues.begin(); it != m_sliceValues.end(); ++it){
        if(!init || *it < min){
            min = *it;
        }
    }
    return min;
}

double PieModel::max() const
{
    double max;
    bool init = false;
    for(auto it = m_sliceValues.begin(); it != m_sliceValues.end(); ++it){
        if(!init || *it > max){
            max = *it;
        }
    }
    return max;
}

void PieModel::fromJson(const QJsonObject &json)
{
    Model::fromJson(json);

    m_sliceValues.clear();
    for(int row = 0; row < rowCount(); ++row){
        double sliceValue = 0;
        for(int column = 0; column < columnCount(); ++column){
            sliceValue += m_chart->itemAt(row)->getValue(column);
        }
        m_sliceValues.push_back(sliceValue);
    }
}
