#ifndef WORLDCREATORRESOURCESWIDGET_H
#define WORLDCREATORRESOURCESWIDGET_H

#include <QWidget>
#include <list>
#include <memory>
#include "Resource.h"
#include "WorldEditor.h"

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
    void chooseTool();
    void setRadius(int radius);
    void setQuantity(int quantity);

private:
    Ui::WorldCreatorResourcesWidget *ui;
    std::list<std::shared_ptr<Resource>> resources;

    WorldEditor editorWidget;
};

#endif // WORLDCREATORRESOURCESWIDGET_H
