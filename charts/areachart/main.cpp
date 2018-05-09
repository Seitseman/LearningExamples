#include <QApplication>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QMainWindow>

#include <memory>

using namespace QtCharts;


int main(int argc, char** argv) {
    QApplication a(argc, argv);

    using namespace std;
    shared_ptr<QLineSeries> series0 = make_shared<QLineSeries>();
    shared_ptr<QLineSeries> series1 = make_shared<QLineSeries>();
    *series0 << QPointF(1,5) << QPointF(3,7) << QPointF(7,6) << QPointF(9,7)
             << QPointF(12,6) << QPointF(16,7) << QPointF(18,5);
    *series1 << QPointF(1,3) << QPointF(3,4) << QPointF(7,3) << QPointF(8,2)
             << QPointF(12,3) << QPointF(16,4) << QPointF(18,3);

    shared_ptr<QAreaSeries> series = make_shared<QAreaSeries>(series0.get(), series1.get());
    series->setName("Batman");
    QPen pen(0x59605);
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0,0), QPointF(0,1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);

    QChart *chart = new QChart();
    chart->addSeries(series.get());
    chart->setTitle("Simple example");
    chart->createDefaultAxes();
    chart->axisX()->setRange(0,20);
    chart->axisY()->setRange(0,10);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);



    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400,300);
    window.show();


    return a.exec();
}
