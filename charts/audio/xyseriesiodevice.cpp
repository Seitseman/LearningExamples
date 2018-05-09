#include "xyseriesiodevice.h"
#include <QtCharts/QXYSeries>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries *series, QObject *parent)
    : QIODevice(parent)
    , mSeries(series)
{

}

qint64 XYSeriesIODevice::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen);
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char *data, qint64 len)
{
    qint64 range = 20000;
    QVector<QPointF> oldPoints = mSeries->pointsVector();
    QVector<QPointF> points;

    int resolution = 4;

    if (oldPoints.count() < range) {
        points  = mSeries->pointsVector();
    } else {
        for (int i =len/resolution; i < oldPoints.count(); ++i) {
            points.append(QPointF(i - len/resolution, oldPoints.at(i).y()));
        }
    }
    quint64 size = points.count();
    for (int k = 0; k < len/resolution; ++k) {
        points.append(QPointF(k+size, ((quint8)data[resolution*k] - 128)/128.0));
    }
    mSeries->replace(points);
    return len;
}
