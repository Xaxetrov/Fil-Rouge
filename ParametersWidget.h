#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QTabWidget>
#include "World.h"
#include "WorldWidget.h"

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit ParametersWidget(QWidget *parent = 0);
    void set(World * world, WorldWidget * worldWidget);
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
    World * m_world;
    WorldWidget * m_worldWidget;
};

#endif // PARAMETERSWIDGET_H
