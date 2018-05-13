#ifndef MAINSLICE_H
#define MAINSLICE_H

#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE

class MainSlice : public QPieSlice
{
    Q_OBJECT
public:
    explicit MainSlice(QPieSeries *breakdownSeries, QObject *parent = nullptr);
    QPieSeries *breakdownSeries() const;

    void setName(const QString& name);
    QString name() const;

public Q_SLOTS:
    void updateLabel();

private:
    QPieSeries *mBreakdownSeries = nullptr;
    QString mName;
};

#endif // MAINSLICE_H
