#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QXmlStreamReader>

#include "WorldWidget.h"
//#include "EntityViewWidget.h"
#include "EntityFrame.h"
#include "World.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void switchTimer();
    void keyPressEvent(QKeyEvent * e);
    void saveNeuraleNetwork(shared_ptr<Animal> a, bool pauseDuringSave);
    void saveNeuraleNetwork();
    void setSelectedAnimal(std::weak_ptr<Animal> a);

private:
    void loadWorld();
    void loadXML(QString worldSave);
    void parseWorld(QXmlStreamReader& reader);
    void parseEntity(QXmlStreamReader& reader);


private:
    //ui
    Ui::MainWindow *ui;
    WorldWidget worldWidget;
    //EntityViewWidget entityWidget;
    EntityFrame entityWidget;
    QMenu * fileMenu;
    QMenu * simulationMenu;
    QMenu * animalMenu;
    QAction * simmulationStartStopAction;
    QAction * fileExitAction;
    QAction * saveNeuraleNetworkAction;

    World world;
    std::weak_ptr<Animal> selectedAnimal;
};

#endif // MAINWINDOW_H
