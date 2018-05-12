#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QTextStream>
#include <QDateTime>
#include <QValueAxis>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>



QT_CHARTS_USE_NAMESPACE

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QLineSeries *series = new QLineSeries;

    //![2]
    // data from http://www.swpc.noaa.gov/ftpdir/weekly/RecentIndices.txt
    // http://www.swpc.noaa.gov/ftpdir/weekly/README
    // http://www.weather.gov/disclaimer
    QFile sunSpots(":sun");
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream stream(&sunSpots);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith("#") || line.startsWith(":")) {
            continue;
        }
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt(), 15));
        series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    sunSpots.close();

    QChart *ch = new QChart;
    ch->addSeries(series);
    ch->legend()->hide();
    ch->setTitle("Sunspots count (by Space Weather Prediction Center)");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    ch->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Sunspots count");
    ch->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(ch);
    view->setRenderHint(QPainter::Antialiasing);

    QMainWindow w;
    w.setCentralWidget(view);
    w.resize(820, 600);
    w.show();
    return a.exec();
}
