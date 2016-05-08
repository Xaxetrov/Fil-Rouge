#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QTabWidget>
#include <QPaintEvent>
#include <QVector>
#include "qcustomplot.h"

namespace Ui {
class TimelineWidget;
}

class TimelineWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = 0);
    void initView();
    void paintEvent(QPaintEvent *event);
    static void updatePopulation(int herbivoresPopulation, int carnivoresPopulation, unsigned int time);
    ~TimelineWidget();

    static QVector<double> time;
    static QVector<double> population;
    static QVector<double> herbivoresPopulation;
    static QVector<double> carnivoresPopulation;

public slots:
    void updateView();

private:
    Ui::TimelineWidget *ui;
    QTimer * updateViewTimer;
    bool isTimerStarted;
};

#endif // TIMELINEWIDGET_H
