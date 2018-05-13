#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include "donutbreakdownchart.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QPieSeries* series1 = new QPieSeries();
    series1->setName("Fossil fuels");
    series1->append("Oil", 353295);
    series1->append("Coal", 188500);
    series1->append("Natural gas", 148680);
    series1->append("Peat", 94545);

    QPieSeries *series2 = new QPieSeries();
    series2->setName("Renewables");
    series2->append("Wood fuels", 319663);
    series2->append("Hydro power", 45875);
    series2->append("Wind power", 1060);

    QPieSeries *series3 = new QPieSeries;
    series3->setName("Others");
    series3->append("Nuclear Energy", 238789);
    series3->append("Import enegy", 37802);
    series3->append("Other", 32441);

    DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart;
    donutBreakdown->setAnimationOptions(QChart::AllAnimations);
    donutBreakdown->setTitle("Total consumption of energy in Finland 2010");
    donutBreakdown->legend()->setAlignment(Qt::AlignRight);
    donutBreakdown->addBreakdownSeries(series1, Qt::red);
    donutBreakdown->addBreakdownSeries(series2, Qt::darkGreen);
    donutBreakdown->addBreakdownSeries(series3, Qt::darkBlue);

    QChartView *view = new QChartView(donutBreakdown);
    view->setRenderHint(QPainter::Antialiasing);

    QMainWindow w;
    w.setCentralWidget(view);
    w.resize(800, 500);
    w.show();

    return a.exec();
}
