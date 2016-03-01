#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void switchTimer();
    void keyPressEvent(QKeyEvent * e);

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
    QAction * simmulationStartStopAction;
    QAction * fileExitAction;

    World world;
};

#endif // MAINWINDOW_H
