#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QtCharts/QChartGlobal>
#include <QObject>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice : public QIODevice
{
public:
    explicit XYSeriesIODevice(QXYSeries* series, QObject* parent = nullptr);

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;


private:
    QXYSeries *mSeries = nullptr;
};

#endif // XYSERIESIODEVICE_H
