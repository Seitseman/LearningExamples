#include "candlestickdatareader.h"

#include <QStringList>

CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : QTextStream(device)
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QCandlestickSet* CandlestickDataReader::readCandleStick()
{
    QString line = readLine();
    if (line.startsWith("#")|| line.isEmpty()) {
        return nullptr;
    }

    QStringList strList = line.split(" ", QString::SkipEmptyParts);
    if (strList.count() != 5) {
        return 0;
    }

    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();

    QCandlestickSet *candleStickSet = new QCandlestickSet(timestamp);
    candleStickSet->setOpen(open);
    candleStickSet->setHigh(high);
    candleStickSet->setLow(low);
    candleStickSet->setClose(close);

    return candleStickSet;
}
