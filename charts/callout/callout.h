#ifndef CALLOUT_H
#define CALLOUT_H

#include <QGraphicsItem>
#include <QtCharts/QChartGlobal>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Callout : public QGraphicsItem
{
public:
    explicit Callout(QChart *chart = nullptr);

    void setText(const QString& text);
    void setAnchor(const QPointF& point);
    void updateGeometry();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString mText;
    QRectF mTextRect;
    QRectF mRect;
    QPointF mAnchor;
    QFont mFont;
    QChart *mChart = nullptr;
};

#endif // CALLOUT_H
