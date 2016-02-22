#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "WorldWidget.h"
#include "EntityViewWidget.h"
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

private slots:
    void switchTimer();

private:
    void loadWorld();


private:
    //ui
    Ui::MainWindow *ui;
    WorldWidget worldWidget;
    EntityViewWidget entityWidget;
    QMenu * fileMenu;
    QMenu * simulationMenu;
    QAction * simmulationStartStopAction;
    QAction * fileExitAction;

    World world;
};

#endif // MAINWINDOW_H
