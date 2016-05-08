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
    void paintEvent(QPaintEvent *event);
    static void updatePopulation(int herbivoresPopulation, int carnivoresPopulation, unsigned int time);
    ~TimelineWidget();

    static QVector<double> time;
    static QVector<double> population;
    static QVector<double> herbivoresPopulation;
    static QVector<double> carnivoresPopulation;

private:
    Ui::TimelineWidget *ui;
};

#endif // TIMELINEWIDGET_H
