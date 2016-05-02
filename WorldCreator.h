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
    explicit WorldCreator(QWidget *parent = 0);
    ~WorldCreator();

public slots:
    void loadWorld();
    void finish();
    void addHerbivoreBrain();
    void addCarnivoreBrain();

private:
    Ui::WorldCreator *ui;
    QTabWidget tabWidget;
    WorldCreatorAnimalsWidget animalWidget;
    WorldCreatorResourcesWidget resourceWidget;
    World world;

    std::list<QString> herbivores;
    std::list<QString> carnivores;

};

#endif // WORLDCREATOR_H
