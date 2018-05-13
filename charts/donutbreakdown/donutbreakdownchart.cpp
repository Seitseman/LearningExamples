#include "donutbreakdownchart.h"
#include "mainslice.h"

#include <QPieLegendMarker>

DonutBreakdownChart::DonutBreakdownChart(QGraphicsItem *parent,
                                         Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
    , mMainSeries(new QPieSeries())
{
    mMainSeries->setPieSize(0.7);
    addSeries(mMainSeries);
}

void DonutBreakdownChart::addBreakdownSeries(QPieSeries *series, QColor color)
{
    QFont font("Arial", 8);

    MainSlice *mainSlice = new MainSlice(series);
    mainSlice->setName(series->name());
    mainSlice->setValue(series->sum());
    mMainSeries->append(mainSlice);

    mainSlice->setBrush(color);
    mainSlice->setLabelVisible(true);
    mainSlice->setLabelColor(Qt::white);
    mainSlice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
    mainSlice->setLabelFont(font);

    series->setPieSize(0.8);
    series->setHoleSize(0.7);
    series->setLabelsVisible(true);
    for (auto* slice : series->slices()) {
        color = color.lighter(115);
        slice->setBrush(color);
        slice->setLabelFont(font);
    }

    QChart::addSeries(series);

    recalculateAngles();
    updateLegendMarkers();
}

void DonutBreakdownChart::recalculateAngles()
{
    qreal angle = 0;
    for(QPieSlice* slice : mMainSeries->slices()) {
        QPieSeries *breakdownSeries = qobject_cast<MainSlice*>(slice)->breakdownSeries();
        breakdownSeries->setPieStartAngle(angle);
        angle += slice->percentage()*360.0;
        breakdownSeries->setPieEndAngle(angle);
    }
}

void DonutBreakdownChart::updateLegendMarkers()
{
    for (auto *subSeries : series()) {
        for (auto *marker: legend()->markers(subSeries)) {
            QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker*>(marker);
            if (subSeries == mMainSeries) {
                pieMarker->setVisible(false);
            } else {
                pieMarker->setLabel(QString("%1 %2%")
                                    .arg(pieMarker->slice()->label())
                                    .arg(pieMarker->slice()->percentage()*100, 0, 'f',2));
                pieMarker->setFont(QFont("Arial", 8));

            }
        }
    }
}
