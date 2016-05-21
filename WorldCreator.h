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

/*
 * The World creator is the containing class for a tool which creates a world with personal parameters
 */
class WorldCreator : public QMainWindow
{
    Q_OBJECT

public:
    //constructor, destructor
    explicit WorldCreator(World * worldToChange = nullptr,QWidget *parent = 0);
    ~WorldCreator();

    //setters
    void setWorldPointer(World *worldToChange) {world = worldToChange;}

public slots:
    //"slot" methods
    void finish();
    void closeEvent(QCloseEvent *e);

signals:
    //"signal" methods
    void actionFinished();

private:
    Ui::WorldCreator *ui;
    QTabWidget tabWidget;
    WorldCreatorAnimalsWidget animalWidget;
    WorldCreatorResourcesWidget resourceWidget;
    World *world;

};

#endif // WORLDCREATOR_H
