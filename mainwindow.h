#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "WorldWidget.h"
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

private:
    void loadWorld();

private:
    Ui::MainWindow *ui;
    WorldWidget worldWidget;
    World world;
};

#endif // MAINWINDOW_H
