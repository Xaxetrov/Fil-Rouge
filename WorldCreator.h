#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include <QMainWindow>

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

private:
    Ui::WorldCreator *ui;
};

#endif // WORLDCREATOR_H
