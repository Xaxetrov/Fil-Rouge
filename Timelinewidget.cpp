#include "Timelinewidget.h"
#include "ui_Timelinewidget.h"
#include "WorldColors.h"
#include <QPainter>
#include <QColor>

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

    isTimerStarted = false;
    initView();

    updateViewTimer = new QTimer(this);
    connect(updateViewTimer, SIGNAL(timeout()), this, SLOT(updateView()));
}

void TimelineWidget::paintEvent(QPaintEvent *event)
{
    if(!isTimerStarted)
    {
      updateView();
      updateViewTimer->start(1000);
      isTimerStarted = true;
    }
}

void TimelineWidget::initView()
{
  // Set layout
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(ui->customPlot);
  setLayout(layout);

  // Title
  ui->customPlot->plotLayout()->insertRow(0);
  ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, "Population"));

  // Legend
  ui->customPlot->xAxis->setLabel("Ticks");
  ui->customPlot->yAxis->setLabel("Population");
  ui->customPlot->legend->setVisible(true);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  ui->customPlot->legend->setFont(legendFont);
  ui->customPlot->legend->setSelectedFont(legendFont);
  ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

  WorldColors colors;
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setPen(QPen(QColor(144, 140, 140)));
  ui->customPlot->graph(0)->setBrush(QBrush(QColor(233, 233, 233)));
  ui->customPlot->graph(0)->setName("Total population");
  ui->customPlot->addGraph();
  ui->customPlot->graph(1)->setPen(QPen(Qt::green));
  ui->customPlot->graph(1)->setName("Herbivores");
  ui->customPlot->addGraph();
  ui->customPlot->graph(2)->setPen(QPen(Qt::red));
  ui->customPlot->graph(2)->setName("Carnivores");

  ui->customPlot->xAxis2->setVisible(true);
  ui->customPlot->xAxis2->setTickLabels(false);
  ui->customPlot->yAxis2->setVisible(true);
  ui->customPlot->yAxis2->setTickLabels(false);

  connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

  setWindowTitle("Timeline");
  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void TimelineWidget::updateView()
{
    if(!this->isVisible())
    {
      updateViewTimer->stop();
      isTimerStarted = false;
      return;
    }

    ui->customPlot->graph(0)->setData(time, population);
    ui->customPlot->graph(1)->setData(time, herbivoresPopulation);
    ui->customPlot->graph(2)->setData(time, carnivoresPopulation);

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);

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
    delete updateViewTimer;
}
