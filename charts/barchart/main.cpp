#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QBarSet* set0 = new QBarSet("Jane");
    QBarSet* set1 = new QBarSet("John");
    QBarSet* set2 = new QBarSet("Axel");
    QBarSet* set3 = new QBarSet("Mary");
    QBarSet* set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set3 << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSeries series;
    series.append(set0);
    series.append(set1);
    series.append(set2);
    series.append(set3);
    series.append(set4);

    QChart *chart = new QChart;
    chart->addSeries(&series);
    chart->setTitle("Bar chart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setDropShadowEnabled(true);

    chart->createDefaultAxes();

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis;
    axis->append(categories);
    chart->setAxisX(axis, &series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(420, 300);
    window.show();


    return a.exec();
}
