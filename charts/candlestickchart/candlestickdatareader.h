#ifndef CANDLESTICKDATAREADER_H
#define CANDLESTICKDATAREADER_H

#include <QtCore/QTextStream>
#include <QtCharts/QCandleStickSet>

QT_CHARTS_USE_NAMESPACE

class CandlestickDataReader : public QTextStream
{
public:
    explicit CandlestickDataReader(QIODevice* device);

    void readFile(QIODevice* device);
    QCandlestickSet *readCandleStick();
};

#endif // CANDLESTICKDATAREADER_H
