#include "tablewidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QVBarModelMapper>

#include "customtablemodel.h"

QT_CHARTS_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    mModel = new CustomTableModel(this);

    QTableView *tableView = new QTableView(this);
    tableView->setModel(mModel);
    tableView->setMinimumWidth(300);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mModel->setParent(tableView);

    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    QBarSeries *series = new QBarSeries;

    int first = 1;
    int count = 5;
    QVBarModelMapper *mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(1);
    mapper->setLastBarSetColumn(5);
    mapper->setFirstRow(first);
    mapper->setRowCount(count);
    mapper->setSeries(series);
    mapper->setModel(mModel);

    chart->addSeries(series);

    QString seriesColorHex = "#000000";

    QList<QBarSet*> barsets = series->barSets();
    for(int i = 0; i < barsets.count(); ++i) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        mModel->addMapping(seriesColorHex, QRect(1 + i, first, 1, barsets.at(i)->count()));
    }

    QStringList categories;
    categories << "April" << "May" << "June" << "July" << "August";
    QBarCategoryAxis *axis = new QBarCategoryAxis;
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1,0);
    mainLayout->addWidget(chartView, 1,1);
    mainLayout->setColumnStretch(1,1);
    mainLayout->setColumnStretch(0,0);
    setLayout(mainLayout);
}
