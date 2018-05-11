#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


class ThemeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = nullptr);
    ~ThemeWidget();

private Q_SLOTS:
    void updateUI();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();

    QChart *createAreaChart() const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createBarChart(int valueCount) const;

    QChart *createSplineChart() const;
    QChart *createScatterChart() const;

    int m_listCount =3;
    int m_valueMax = 10;
    int m_valueCount = 7;
    QList<QChartView*> m_charts;
    DataTable m_dataTable;

    Ui_ThemeWidgetForm *m_ui = nullptr;
};

#endif // THEMEWIDGET_H
