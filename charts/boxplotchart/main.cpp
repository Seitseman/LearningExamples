#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QFile>
#include <QChart>
#include <QChartView>

#include <QtCharts/QBoxPlotSeries>

#include "boxdatareader.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
    acmeSeries->setName("Acme Ltd");

    QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries();
    boxWhiskSeries->setName("BoxWhisk Inc");

    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    BoxDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet* set = dataReader.readBox();
        if (set) {
            acmeSeries->append(set);
        }
    }

    QFile boxWhiskData(":boxwhisk");
    if (!boxWhiskData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    dataReader.readFile(&boxWhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set) {
            boxWhiskSeries->append(set);
        }
    }

    QChart * chart = new QChart;
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("Acme Ltd and BoxWhisk Inc share deviation in 2012");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    chart->createDefaultAxes();
    chart->axisY()->setMin(15.0);
    chart->axisY()->setMax(34.0);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow w;
    w.setCentralWidget(chartView);
    w.resize(800,600);
    w.show();

    return a.exec();
}
