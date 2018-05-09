#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

class QAudioInput;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    XYSeriesIODevice *mDevice = nullptr;
    QChart *mChart = nullptr;
    QLineSeries *mSeries = nullptr;
    QAudioInput *mAudioInput = nullptr;

};

#endif // WIDGET_H
