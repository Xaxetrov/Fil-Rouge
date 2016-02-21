#include "EntityViewWidget.h"
#include "config/config.h"

EntityViewWidget::EntityViewWidget(Animal *a): QGraphicsView(), animal(a)
{
    setScene(&scene);
}

void EntityViewWidget::updateView()
{
    scene.clear();
    QPen & borderPen = colors.getEntityPen(animal);
    QBrush & backgroundBrush = colors.getBackgroundBrush();
    //draw base vision sector
    for(int i=0 ; i<NB_VISIONSECTORS_LIVING ; i++)
    {
        QPolygonF visionSector;
        visionSector = generateVisionSector(VISIONSECTORS_LIVING[i][0],VISIONSECTORS_LIVING[i][1],VISIONSECTORS_LIVING[i][2]);
        scene.addPolygon(visionSector,borderPen,backgroundBrush);
    }
    //draw viewed vision sector
    //TODO
    //draw entity
    QRect baseSquare(-10,-10,20,20);
    scene.addEllipse(baseSquare,borderPen,colors.getEntityBrush(animal));
    QRect eyebaseSquare(-3,-10,6,6);
    scene.addEllipse(eyebaseSquare,borderPen,colors.getTeamsEyeBrush());
}

QPolygonF EntityViewWidget::generateVisionSector(int angle1, int angle2, int depth, int numberOfPoint) const
{
    QPolygonF ret;
    ret.push_back(QPoint(0,0));//add the center of the entity
    double deltaAngle( (angle2-angle1)/(numberOfPoint-1));
    double angle = angle1;
    for(double i=0 ; i<numberOfPoint ; i++)
    {
        ret.push_back(QPoint(depth*cos(angle*PI/180.0-PI/2.0),depth*sin(angle*PI/180.0-PI/2.0)));
        angle += deltaAngle;
    }
    return ret;
}

void EntityViewWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(-45,-110,90,120,Qt::KeepAspectRatio);
}

void EntityViewWidget::setAnimal(Animal *a)
{
    animal = a;
    updateView();
}


