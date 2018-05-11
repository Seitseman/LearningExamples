#include "themewidget.h"
#include "ui_themewidget.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

#include <QRandomGenerator>
#include <QtWidgets/QComboBox>

#include <QBarSet>
#include <QPieSeries>
#include <QScatterSeries>

#include <QSplineSeries>
#include <QStackedBarSeries>
#include <QValueAxis>

ThemeWidget::ThemeWidget(QWidget *parent)
    : QWidget(parent)
    , m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))
    , m_ui( new Ui_ThemeWidgetForm)
{
    m_ui->setupUi(this);
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    QChartView *chartView = new QChartView(createAreaChart());
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createPieChart());
//    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

    chartView = new QChartView(createLineChart());
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;

    chartView = new QChartView(createBarChart(m_valueCount));
    m_ui->gridLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart());
    m_ui->gridLayout->addWidget(chartView, 2,1);
    m_charts << chartView;

    chartView = new QChartView(createScatterChart());
    m_ui->gridLayout->addWidget(chartView, 2,2);
    m_charts << chartView;

     m_ui->antialiasCheckBox->setChecked(true);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    updateUI();
}

ThemeWidget::~ThemeWidget()
{
    delete m_ui;
}

void ThemeWidget::updateUI()
{
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
                m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex()).toInt());

    const auto charts = m_charts;
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView : charts) {
            chartView->chart()->setTheme(theme);
        }

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    bool checked = m_ui->antialiasCheckBox->isChecked();
    for (QChartView* chart: charts) {
        chart->setRenderHint(QPainter::Antialiasing, checked);
    }

    QChart::AnimationOptions options(m_ui->animatedComboBox->itemData(
                                         m_ui->animatedComboBox->currentIndex()).toInt());
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
        for (const auto * chartView: charts) {
            chartView->chart()->setAnimationOptions(options);
        }
    }

    Qt::Alignment alignment(m_ui->legendComboBox->itemData(
                                m_ui->legendComboBox->currentIndex()).toInt());

    if(!alignment) {
        for(const auto* chartView: charts) {
            chartView->chart()->legend()->hide();
        }
    } else {
        for (const auto* chartView: charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
}

DataTable ThemeWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    for (int i = 0; i < listCount; ++i) {
        DataList dataList;
        qreal yValue(0);
        for (int j = 0; j < valueCount; ++j) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax/(qreal)valueCount);
            QPointF value ((j + QRandomGenerator::global()->generateDouble())*
                           ((qreal)m_valueMax/valueCount)
                           , yValue);
            QString label = "Slice: " + QString::number(i) + ":" + QString::number(j);
            dataList <<Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

void ThemeWidget::populateThemeBox()
{
    m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox()
{
    m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    m_ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    m_ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void ThemeWidget::populateLegendBox()
{
    m_ui->legendComboBox->addItem("No Legend ", 0);
    m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}

QChart* ThemeWidget::createAreaChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Area chart");

    QLineSeries *lowerSeries = nullptr;
    QString name("Series ");
    int nameIndex = 0;
    for (int i{0}; i <  m_dataTable.count(); ++i) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j{0}; j < m_dataTable[i].count(); ++j) {
            Data data = m_dataTable[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF>& points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        lowerSeries = upperSeries;
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, m_valueCount - 1);
    chart->axisY()->setRange(0, m_valueMax);
    static_cast<QValueAxis*>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

QChart* ThemeWidget::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    QPieSeries *series = new QPieSeries(chart);
    for (const Data & data: m_dataTable[0]) {
        QPieSlice *slice = series->append(data.second, data.first.y());
        if (data == m_dataTable[0].first()) {
            slice->setLabelVisible();
            slice->setExploded();
            slice->setExplodeDistanceFactor(0.5);
        }
    }

    series->setPieSize(0.4);
    chart->addSeries(series);

    return chart;
}

QChart *ThemeWidget::createLineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Line chart");

    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : m_dataTable) {
        QLineSeries *series = new QLineSeries(chart);
        for (const Data& data : list) {
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    return chart;
}

QChart *ThemeWidget::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount)
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i{0}; i < m_dataTable.count(); ++i) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data& data: m_dataTable[i]) {
            *set << data.first.y();
        }
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axisY()->setRange(0, m_valueMax*2);
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ThemeWidget::createSplineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    for(const DataList& list : m_dataTable) {
        QSplineSeries *series = new QSplineSeries(chart);
        for(const Data &data: list) {
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, m_valueMax);
    chart->axisY()->setRange(0, m_valueCount);

    static_cast<QValueAxis*>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ThemeWidget::createScatterChart() const
{
    // scatter chart
    QChart *chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : m_dataTable) {
        QScatterSeries *series = new QScatterSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, m_valueMax);
    chart->axisY()->setRange(0, m_valueCount);
    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}
