#include "chart.h"

#include <QtCore/QtMath>

#include <QtCharts/QValueAxis>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags, QLineSeries *series)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
    , mSeries(series)
{
    mClicked = false;
}

void Chart::clickPoint(const QPointF &point)
{
    mMovingPoint = QPoint();
    mClicked = false;
    const auto points = mSeries->points();
    for (QPointF p : points) {
        if (distance(p, point) < distance(mMovingPoint, point)) {
            mMovingPoint = p;
            mClicked = true;
        }
    }
}

void Chart::handlePointMove(const QPoint &point)
{
    if(mClicked) {
        QPoint mappePoint = point;
        mappePoint.setX(point.x() - this->plotArea().x());
        mappePoint.setY(point.y() - this->plotArea().y());

        QAbstractAxis *axisx = this->axisX();
        QValueAxis *haxis = nullptr;
        if (axisx->type() ==QAbstractAxis::AxisTypeValue) {
            haxis = qobject_cast<QValueAxis*>(axisx);
        }

        QAbstractAxis *axisy = this->axisY();
        QValueAxis *vaxis = nullptr;
        if(axisy->type() == QAbstractAxis::AxisTypeValue) {
            vaxis = qobject_cast<QValueAxis*>(axisy);
        }

        if (haxis && vaxis) {
            qreal xUnit = plotArea().width()/haxis->max();
            qreal yUnit = plotArea().height()/vaxis->max();

            qreal x = mappePoint.x() / xUnit;
            qreal y = vaxis->max() - mappePoint.y() /yUnit;

            mSeries->replace(mMovingPoint, QPointF(x,y));

            mMovingPoint.setX(x);
            mMovingPoint.setY(y);
        }
    }
}

void Chart::setPointClicked(bool clicked)
{
    mClicked = clicked;
}

qreal Chart::distance(const QPointF &p1, const QPointF &p2)
{
    return qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
}
