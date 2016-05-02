#ifndef WORLDCREATORRESOURCESWIDGET_H
#define WORLDCREATORRESOURCESWIDGET_H

#include <QWidget>

namespace Ui {
class WorldCreatorResourcesWidget;
}

class WorldCreatorResourcesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorldCreatorResourcesWidget(QWidget *parent = 0);
    ~WorldCreatorResourcesWidget();

private:
    Ui::WorldCreatorResourcesWidget *ui;
};

#endif // WORLDCREATORRESOURCESWIDGET_H
