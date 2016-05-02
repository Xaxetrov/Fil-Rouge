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

    bool isHerbivoreChecked();
    bool isCarnivoreChecked();

private:
    Ui::WorldCreatorAnimalsWidget *ui;
    QStringListModel *listModel;
};

#endif // WORLDCREATORANIMALSWIDGET_H
