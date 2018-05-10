#ifndef BOXDATAREADER_H
#define BOXDATAREADER_H

#include <QtCore/QTextStream>
#include <QtCharts/QBoxSet>

QT_CHARTS_USE_NAMESPACE

class BoxDataReader : public QTextStream
{
public:
    explicit BoxDataReader(QIODevice* device);
    void readFile(QIODevice *device);
    QBoxSet *readBox();

protected:
    qreal findMedian(int begin, int end) const;

private:
    QList<qreal> sortedList;
};

#endif // BOXDATAREADER_H
