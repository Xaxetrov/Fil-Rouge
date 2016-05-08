#include "Timelinewidget.h"
#include "ui_Timelinewidget.h"
#include "WorldColors.h"
#include <QPainter>
#include <QColor>

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QHBoxLayout>

#include <iostream>
using namespace std;

QVector<double> TimelineWidget::time;
QVector<double> TimelineWidget::population;
QVector<double> TimelineWidget::herbivoresPopulation;
QVector<double> TimelineWidget::carnivoresPopulation;

TimelineWidget::TimelineWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TimelineWidget)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->customPlot);
    setLayout(layout);
}

void TimelineWidget::paintEvent(QPaintEvent *event)
{
    WorldColors colors;
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(144, 140, 140)));
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(233, 233, 233)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::green));
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::red));

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);

    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    ui->customPlot->graph(0)->setData(time, population);
    ui->customPlot->graph(1)->setData(time, herbivoresPopulation);
    ui->customPlot->graph(2)->setData(time, carnivoresPopulation);
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    setWindowTitle("Timeline");
    ui->customPlot->replot();
}

void TimelineWidget::updatePopulation(int herbivoresPopulation, int carnivoresPopulation, unsigned int time)
{
  TimelineWidget::time.append(time);
  TimelineWidget::population.append(herbivoresPopulation + carnivoresPopulation);
  TimelineWidget::herbivoresPopulation.append(herbivoresPopulation);
  TimelineWidget::carnivoresPopulation.append(carnivoresPopulation);
}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}
