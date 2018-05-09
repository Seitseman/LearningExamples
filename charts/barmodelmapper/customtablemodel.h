#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject *parent = nullptr);
    virtual ~CustomTableModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addMapping(const QString& color, const QRect& area);
    void clearMapping() { mMapping.clear();}

private:
    QList<QVector<qreal> *> mData;
    QHash<QString, QRect> mMapping;

    int mColumnCount = 6;
    int mRowCount = 12;
};

#endif // CUSTOMTABLEMODEL_H
