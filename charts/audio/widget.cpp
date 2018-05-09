#include "widget.h"
#include "xyseriesiodevice.h"
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QVBoxLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    mChart = new QChart;
    QChartView *chartView = new QChartView(mChart, this);
    chartView->setMinimumSize(800, 600);

    mSeries = new QLineSeries;
    mChart->addSeries(mSeries);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,20000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio Level");

    mChart->setAxisX(axisX, mSeries);
    mChart->setAxisY(axisY, mSeries);
    mChart->setTitle("Data From the microphone");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    if (inputDevices.isFormatSupported(formatAudio)) {
        formatAudio = inputDevices.nearestFormat(formatAudio);
    }
    mAudioInput = new QAudioInput(inputDevices, formatAudio, this);

    mDevice = new XYSeriesIODevice(mSeries, this);
    mDevice->open(QIODevice::WriteOnly);
    mAudioInput->start(mDevice);
}


Widget::~Widget() {
    mAudioInput->stop();
    mDevice->close();
}
