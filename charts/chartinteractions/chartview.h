#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

class Chart;

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    explicit ChartView(Chart* chart, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Chart* mChart = nullptr;
    QPoint mMousePoint;
};

#endif // CHARTVIEW_H
