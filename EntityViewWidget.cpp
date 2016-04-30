#include "EntityViewWidget.h"
#include "config/config.h"

#include <iostream>

EntityViewWidget::EntityViewWidget(std::weak_ptr<Animal> a): QGraphicsView(), animal(a)
{
    setScene(&scene);
}

void EntityViewWidget::updateView()
{
    std::shared_ptr<Animal> sharedAnimal = animal.lock();
    scene.clear();
    QPen & borderPen = colors.getEntityPen(sharedAnimal);
    QBrush & backgroundBrush = colors.getBackgroundBrush();
    ///draw vision sector
    //draw base vision sector
    for(unsigned i=0 ; i<NB_VISIONSECTORS_LIVING ; i++)
    {
       QPolygonF visionSector;
       visionSector = generateVisionSector(VISIONSECTORS_LIVING[i][0],VISIONSECTORS_LIVING[i][1],VISIONSECTORS_LIVING[i][2]);
       scene.addPolygon(visionSector,borderPen,backgroundBrush);
    }
    //draw filled part of vision sector
    if(sharedAnimal != nullptr)
    {
        const std::vector<std::shared_ptr<Percepted>> & percepted = sharedAnimal->getVision()->getPercepted();
        for(unsigned i=0 ; i<NB_VISIONSECTORS_LIVING && i<percepted.size(); i++)
        {
            if(percepted[i]->getEntity() != nullptr)
            {
                QPolygonF filledVision;
                filledVision = generateVisionSector(VISIONSECTORS_LIVING[i][0],VISIONSECTORS_LIVING[i][1],percepted[i]->getDistance());
                scene.addPolygon(filledVision,borderPen,colors.getEntityBrush(percepted[i]->getEntity()));
            }
        }
    }
    //draw currant entity
    QRect baseSquare(-10,-10,20,20);
    scene.addEllipse(baseSquare,borderPen,colors.getEntityBrush(sharedAnimal));
    QRect eyebaseSquare(-3,-10,6,6);
    scene.addEllipse(eyebaseSquare,borderPen,colors.getTeamsEyeBrush());
}

QPolygonF EntityViewWidget::generateVisionSector(double angle1, double angle2, int depth, int numberOfPoint) const
{
    QPolygonF ret;
    ret.push_back(QPoint(0,0));//add the center of the entity
    double deltaAngle( (angle2-angle1)/(numberOfPoint-1));
    double angle = angle1;
    for(double i=0 ; i<numberOfPoint ; i++)
    {
        ret.push_back(QPoint(depth*cos(angle-PI/2.0),depth*sin(angle-PI/2.0)));
        angle += deltaAngle;
    }
    return ret;
}

void EntityViewWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(this->sceneRect(),Qt::KeepAspectRatio);
}

void EntityViewWidget::setAnimal(std::weak_ptr<Animal> a)
{
    animal = a;
    updateView();
}
