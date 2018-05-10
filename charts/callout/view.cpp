#include "view.h"

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QResizeEvent>

#include "callout.h"

View::View(QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mChart = new QChart;
    mChart->setMinimumSize(640,480);
    mChart->setTitle("Hover the line to show callout. Click the line to make it stay");
    mChart->legend()->hide();
    QLineSeries *series = new QLineSeries;
    series->append(1,3);
    series->append(4,5);
    series->append(5,4.5);
    series->append(7,1);
    series->append(11,2);
    mChart->addSeries(series);

    QSplineSeries *series2 = new QSplineSeries;
    series2->append(1.6, 1.4);
    series2->append(2.4, 3.5);
    series2->append(3.7, 2.5);
    series2->append(7,4);
    series2->append(10, 2);
    mChart->addSeries(series2);

    mChart->createDefaultAxes();
    mChart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(mChart);

    mCoordX = new QGraphicsSimpleTextItem(mChart);
    mCoordX->setPos(mChart->size().width()/2 - 50, mChart->size().height());
    mCoordX->setText("X: ");

    mCoordY = new QGraphicsSimpleTextItem(mChart);
    mCoordY->setPos(mChart->size().width()/2 + 50, mChart->size().height());
    mCoordY->setText("Y: ");

    connect(series, &QLineSeries::clicked, this, &View::keepCallout);
    connect(series, &QLineSeries::hovered, this, &View::toolTip);

    connect(series2, &QLineSeries::clicked, this, &View::keepCallout);
    connect(series2, &QLineSeries::hovered, this, &View::toolTip);

    this->setMouseTracking(true);
}


void View::resizeEvent(QResizeEvent *event)
{
    if(scene()) {
        scene()->setSceneRect(QRect(QPoint(0,0), event->size()));
        mChart->resize(event->size());
        if (mCoordX) {
            mCoordX->setPos(mChart->size().width()/2 - 50, mChart->size().height() - 20);
        }
        if (mCoordY) {
            mCoordY->setPos(mChart->size().width()/2 + 50, mChart->size().height() - 20);
        }
        const auto callouts = mCallouts;
        for(Callout *callout : callouts) {
            callout->updateGeometry();
        }
    }
    QGraphicsView::resizeEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    mCoordX->setText(QString("X: %1").arg(mChart->mapToValue(event->pos()).x()));
    mCoordY->setText(QString("Y: %1").arg(mChart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void View::keepCallout()
{
    mCallouts.append(mTooltip);
    mTooltip = new Callout(mChart);
}

void View::toolTip(QPointF point, bool state)
{
    if(mTooltip == nullptr) {
        mTooltip = new Callout(mChart);
    }

    if (state) {
        mTooltip->setText(QString("X: %1\nY: %2 ").arg(point.x()).arg(point.y()));
        mTooltip->setAnchor(point);
        mTooltip->setZValue(11);
        mTooltip->updateGeometry();
        mTooltip->show();
    } else {
        mTooltip->hide();
    }
}
