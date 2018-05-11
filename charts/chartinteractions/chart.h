#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
    Q_OBJECT
public:
    explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = 0,
                   QLineSeries *series = nullptr);

public slots:
    void clickPoint(const QPointF & point);

public:
    void handlePointMove(const QPoint &point);
    void setPointClicked(bool clicked);

private:
    qreal distance(const QPointF& p1, const QPointF& p2);

    QLineSeries* mSeries = nullptr;
    QPointF mMovingPoint;

    bool mClicked = false;
};

#endif // CHART_H
