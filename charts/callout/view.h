#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Callout;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    void keepCallout();
    void toolTip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *mCoordX = nullptr;
    QGraphicsSimpleTextItem *mCoordY = nullptr;
    QChart *mChart = nullptr;
    Callout *mTooltip = nullptr;
    QList<Callout*> mCallouts;
};

#endif // VIEW_H
