#include "chartview.h"

#include "chart.h"

ChartView::ChartView(Chart *chart, QWidget *parent)
    : QChartView(chart, parent)
    , mChart(chart)
{
}

void ChartView::mousePressEvent(QMouseEvent *e)
{
    mMousePoint = e->pos();
    QChartView::mousePressEvent(e);
}

void ChartView::mouseMoveEvent(QMouseEvent *e)
{
    mChart->handlePointMove(e->pos());
    QChartView::mouseMoveEvent(e);
}

void ChartView::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->pos() != mMousePoint) {
        mChart->handlePointMove(e->pos());
        mChart->setPointClicked(false);
    }
    QChartView::mouseReleaseEvent(e);
}
