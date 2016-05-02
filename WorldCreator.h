#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include <QMainWindow>
#include <QTabWidget>

#include "WorldCreatorAnimalsWidget.h"
#include "WorldCreatorResourcesWidget.h"

namespace Ui {
class WorldCreator;
}

class WorldCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorldCreator(QWidget *parent = 0);
    ~WorldCreator();

private:
    Ui::WorldCreator *ui;
    WorldCreatorAnimalsWidget animalWidget;
    WorldCreatorResourcesWidget resourceWidget;
};

#endif // WORLDCREATOR_H
