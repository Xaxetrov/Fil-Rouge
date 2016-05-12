#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QTabWidget>

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit ParametersWidget(QWidget *parent = 0);
    ~ParametersWidget();

private:
    Ui::ParametersWidget *ui;
};

#endif // PARAMETERSWIDGET_H
