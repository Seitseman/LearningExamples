#include "mainslice.h"

MainSlice::MainSlice(QPieSeries *breakdownSeries, QObject *parent)
    : QPieSlice(parent)
    , mBreakdownSeries(breakdownSeries)
{
    connect(this, &MainSlice::percentageChanged, this, &MainSlice::updateLabel);
}

QPieSeries *MainSlice::breakdownSeries() const
{
    return mBreakdownSeries;
}

void MainSlice::setName(const QString &name)
{
    mName = name;
}

QString MainSlice::name() const
{
    return mName;
}

void MainSlice::updateLabel()
{
    setLabel(QString("%1 %2%").arg(mName).arg(percentage()*100, 0, 'f', 2));
}
