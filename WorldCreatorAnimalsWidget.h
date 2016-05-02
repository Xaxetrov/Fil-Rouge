#ifndef WORLDCREATORANIMALSWIDGET_H
#define WORLDCREATORANIMALSWIDGET_H

#include <QWidget>

namespace Ui {
class WorldCreatorAnimalsWidget;
}

class WorldCreatorAnimalsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorldCreatorAnimalsWidget(QWidget *parent = 0);
    ~WorldCreatorAnimalsWidget();

    void addToHerbivoreList(QString path);
    void addToCarnivoreList(QString path);

private:
    Ui::WorldCreatorAnimalsWidget *ui;
};

#endif // WORLDCREATORANIMALSWIDGET_H
