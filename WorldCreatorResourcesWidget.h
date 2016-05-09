#ifndef WORLDCREATORRESOURCESWIDGET_H
#define WORLDCREATORRESOURCESWIDGET_H

#include <QWidget>
#include <list>
#include <memory>
#include "Resource.h"

namespace Ui {
class WorldCreatorResourcesWidget;
}

class WorldCreatorResourcesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorldCreatorResourcesWidget(QWidget *parent = 0);
    ~WorldCreatorResourcesWidget();
    std::list<std::shared_ptr<Resource>> getResources(){return resources;}

public slots:
    void loadWorld();

private:
    Ui::WorldCreatorResourcesWidget *ui;
    std::list<std::shared_ptr<Resource>> resources;
};

#endif // WORLDCREATORRESOURCESWIDGET_H
