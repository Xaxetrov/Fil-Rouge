#ifndef WORLDCREATORANIMALSWIDGET_H
#define WORLDCREATORANIMALSWIDGET_H

#include <QWidget>
#include <QStringListModel>

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
    void removeFromHerbivoreList(int index);
    void removeFromCarnivoreList(int index);

    bool isHerbivoreChecked();
    bool isCarnivoreChecked();

    unsigned getNumberOfHerbivore();
    unsigned getNumberOfCarnivore();

public slots:
    void addHerbivore();
    void addCarnivore();
    //void removeSelectedHerbivore();
    //void removeSelectedCarnivore();

private:
    Ui::WorldCreatorAnimalsWidget *ui;
    QStringListModel *herbivoreListModel;
    QStringListModel *carnivoreListModel;
    QStringList herbivoreList;
    QStringList carnivoreList;
};

#endif // WORLDCREATORANIMALSWIDGET_H
