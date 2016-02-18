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

private slots:
    void on_actionQuit_triggered();

    void on_actionStartTimer_triggered();

    void on_actionStop_triggered();

private:
    void loadWorld();

private:
    Ui::MainWindow *ui;
    WorldWidget worldWidget;
    World world;
};

#endif // MAINWINDOW_H
