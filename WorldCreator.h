#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include <QMainWindow>
#include <QTabWidget>

#include <list>

#include "WorldCreatorAnimalsWidget.h"
#include "WorldCreatorResourcesWidget.h"
#include "World.h"

namespace Ui {
class WorldCreator;
}

class WorldCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorldCreator(World * worldToChange = nullptr,QWidget *parent = 0);
    ~WorldCreator();

    void setWorldPointer(World *worldToChange) {world = worldToChange;}

public slots:
    void finish();
    void closeEvent(QCloseEvent *e);

signals:
    void actionFinished();

private:
    Ui::WorldCreator *ui;
    QTabWidget tabWidget;
    WorldCreatorAnimalsWidget animalWidget;
    WorldCreatorResourcesWidget resourceWidget;
    World *world;

};

#endif // WORLDCREATOR_H
