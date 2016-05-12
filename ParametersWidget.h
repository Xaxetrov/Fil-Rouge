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
    void showEvent( QShowEvent* event );
    ~ParametersWidget();

public slots:
    void updateUIParam();
    void updateWorldParam();
    void updateResourcesParam();
    void updateAnimalsParam();
    void updateHerbivoresParam();
    void updateCarnivoresParam();
    void updateNeuralNetworksParam();

private:
    Ui::ParametersWidget *ui;
};

#endif // PARAMETERSWIDGET_H
