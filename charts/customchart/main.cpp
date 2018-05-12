#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>


QT_CHARTS_USE_NAMESPACE

int main(int argc, char**argv)
{
    QApplication a(argc, argv);

    QLineSeries*series = new QLineSeries;
    *series << QPointF(0,6) << QPointF(9,4) << QPointF(15,20) << QPointF(25,12) <<
               QPointF(29,26);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    QPen pen(QRgb(0xfdb157));
    pen.setWidth(5);
    series->setPen(pen);

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle("Customchart example");

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0,0));
    backgroundGradient.setFinalStop(QPointF(0,1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);

    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0,1));
    plotAreaGradient.setFinalStop(QPointF(1,0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99,0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(true);

    axisX->append("low", 10);
    axisX->append("optimal", 20);
    axisX->append("high", 30);
    axisX->setRange(0,30);

    axisY->append("slow", 10);
    axisY->append("med", 20);
    axisY->append("fast",30);
    axisY->setRange(0,30);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow w;
    w.setCentralWidget(chartView);
    w.resize(400, 300);
    w.show();

    return a.exec();
}
