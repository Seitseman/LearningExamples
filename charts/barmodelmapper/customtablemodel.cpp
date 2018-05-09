#include "customtablemodel.h"
#include <QtCore/QRandomGenerator>
#include <QColor>

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    for(int i = 0; i < mRowCount; ++i) {
        QVector<qreal>* dataVec = new QVector<qreal>(mColumnCount);
        for(int k = 0; k < mColumnCount; ++k) {
            if (k %2 == 0) {
                dataVec->replace(k, i*50+QRandomGenerator::global()->bounded(20));
            } else {
                dataVec->replace(k, QRandomGenerator::global()->bounded(20));
            }
        }
        mData.append(dataVec);
    }
}

CustomTableModel::~CustomTableModel()
{
    qDeleteAll(mData);
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mData.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mColumnCount;
}

QVariant CustomTableModel::headerData(int section,
                                      Qt::Orientation orientation,
                                      int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return QString("201%1").arg(section);
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return mData[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : mMapping) {
            if (rect.contains(index.column(), index.row())){
                return QColor(mMapping.key(rect));
            }
        }
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole) {
        mData[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(const QString &color, const QRect &area)
{
    mMapping.insertMulti(color, area);
}
