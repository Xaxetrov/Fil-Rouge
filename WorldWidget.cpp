#include <cmath>
#include <QWheelEvent>
#include <QFileDialog>
#include <iostream>
#include <QPainter>
#include <QImage>
#include <QGraphicsPixmapItem>

#include "WorldWidget.h"
#include "Animal.h"
#include "Vegetal.h"
#include "Water.h"
#include "Meat.h"
#include "SaveManager.h"


WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
    //setup default selected animal
    selectedAnimal = std::weak_ptr<Animal>();

    //setup a new scene
    m_scene = new QGraphicsScene();
    this->setScene(m_scene);

    //eneable map style navigation
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //disable scroll bar as counter intuitive
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set timer:
    timer.setInterval(config::UPDATE_TIMER_INTERVALE);

    //signal and slot connection
    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
}

WorldWidget::~WorldWidget()
{
    delete m_scene;
}

void WorldWidget::setWorld(World *world)
{
    m_world = world;
    this->updateScene();
    //fit the scene in the view
    this->fitInView(0,0,2*m_world->getSizeX(),2*m_world->getSizeY(),Qt::KeepAspectRatio); //why 2* ??? but it work more or less
}

void WorldWidget::updateScene()
{
    //clear the scene:
    m_scene->clear();
    m_scene->setSceneRect(0,0,m_world->getSizeX(),m_world->getSizeY());
    m_scene->setBackgroundBrush(QBrush(Qt::gray));
    m_scene->addRect(0,0,m_world->getSizeX(),m_world->getSizeY(),QPen(Qt::gray),colors.getBackgroundBrush());
    //add each entity to the scene one by one:
    std::list<std::shared_ptr<Entity>> & entities = m_world->getEntities();
    for(std::shared_ptr<Entity> ite : entities)
    {
        drawEntity(ite);
    }
    emit sceneUpdated();
}

void WorldWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(0,0,config::WORLD_SIZE_X,config::WORLD_SIZE_Y,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(e);
}

void WorldWidget::wheelEvent(QWheelEvent* e)
{
    QPoint numDegree = e->angleDelta() /8;
    qreal factor = std::pow(1.01, numDegree.ry());
    this->scale(factor, factor);
}

void WorldWidget::selectAnimal(std::weak_ptr<Animal> a)
{
    selectedAnimal = a;
    emit animalSelected(a);
    updateScene();
}

void WorldWidget::tick()
{
    m_world->tick();
    updateScene();
}

//timer managment
void WorldWidget::startSimulation()
{
    timer.start();
}
void WorldWidget::suspendSimulation()
{
    timer.stop();
}
bool WorldWidget::isSimulationRunning() const
{
    return timer.isActive();
}



void WorldWidget::drawEntity(const std::shared_ptr<Entity> e)
{
    ///TODO implemente toric view on diagonals
   double x=e->getCoordinate().getX(), y=e->getCoordinate().getY();
   double radius = e->getRadius();
   std::vector<QPoint> positions;
   positions.push_back(QPoint(x,y));
   if(x<radius)
   {
       positions.push_back(QPoint(x+config::WORLD_SIZE_X,y));
   }
   else if(x>config::WORLD_SIZE_X-radius)
   {
       positions.push_back(QPoint(x-config::WORLD_SIZE_X,y));
   }
   if(y<radius)
   {
       positions.push_back(QPoint(x,y+config::WORLD_SIZE_Y));
   }
   else if(y>config::WORLD_SIZE_Y-radius)
   {
       positions.push_back(QPoint(x,y-config::WORLD_SIZE_Y));
   }

   if(const std::shared_ptr<Animal> living = std::dynamic_pointer_cast<Animal>(e))
   {
       for(QPoint pos:positions)
       {
           drawAnimal(living,pos);
       }

       if(living == selectedAnimal.lock())
       {
           std::vector<std::shared_ptr<Percepted>> percepted = living->getVision()->getPercepted();
           for(std::shared_ptr<Percepted> p:percepted)
           {
               const std::shared_ptr<Entity> e = p->getEntity();
               if(e != nullptr)
               {
                   Coordinate c = e->getCoordinate();
                   m_scene->addEllipse(c.getX()-5,c.getY()-5,10,10,QPen(Qt::red));
               }
           }
       }
   }
   else
   {
       for(QPoint pos:positions)
       {

          QBrush brush = colors.getEntityBrush(e);
          QPen pen = colors.getEntityPen(e);
          if(const std::shared_ptr<Resource> resource = std::dynamic_pointer_cast<Resource>(e))
          {
            // Add transparency
            double transparency = ((double)resource->getQuantity()) / ((double)resource->getMaxQuantity());
            brush.setColor(QColor(brush.color().red(), brush.color().green(), brush.color().blue(), transparency * 255.0));
            pen.setColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue(), transparency * 255.0));
          }
          drawBasicEntity(pos,radius,colors.getEntityBrush(e),colors.getEntityPen(e));
       }
   }
}


void WorldWidget::drawAnimal(QPoint pos, double radius, double angle, QBrush brush, QPen pen)
{
    drawBasicEntity(pos,radius,brush,pen);
    //add an eye to show the looking direction
    double eyeRadius = radius/3;
    double eyeXCenter = pos.x()+cos(angle)*(radius-eyeRadius);
    double eyeYCenter = pos.y()+sin(angle)*(radius-eyeRadius);
    QRect eyeSquare(eyeXCenter-eyeRadius,eyeYCenter-eyeRadius,eyeRadius*2,eyeRadius*2);
    QBrush eyeBrush = colors.getTeamsEyeBrush();
    m_scene->addEllipse(eyeSquare,pen,eyeBrush);
}

void WorldWidget::drawAnimal(const std::shared_ptr<Animal> animal)
{
    QPoint pos(animal->getX(),animal->getY());
    drawAnimal(animal,pos);
}

void WorldWidget::drawAnimal(const std::shared_ptr<Animal> animal, QPoint pos)
{
    QPen animalPen;
    if(animal == selectedAnimal.lock())
        animalPen = colors.getTeamsSelectedPen();
    else
        animalPen = colors.getEntityPen(animal);
    drawAnimal(pos,animal->getRadius(),animal->getAngle(),colors.getEntityBrush(animal),animalPen);

    /*QImage image("../Fil-Rouge/sprites/pig30.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    double scale = ((double)animal->getRadius()) / ((double)image.width()) * 3;
    item->setScale(scale);
    item->setTransformOriginPoint(((double)image.width()) / 2, ((double)image.height()) / 2);
    item->setRotation(animal->getAngle() * (180.0 / 3.141592));
    //item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    m_scene->addItem(item);
    item->setPos(pos.x() - ((double)image.width()) / 2, pos.y() - ((double)image.height()) / 2);*/
}

void WorldWidget::drawBasicEntity(QPoint pos, double radius, QBrush brush, QPen pen)
{
    QRect baseSquare(pos.x()-radius,pos.y()-radius,2*radius,2*radius);
    m_scene->addEllipse(baseSquare,pen,brush);
}

void WorldWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF point = this->mapToScene(event->pos());
    for(std::shared_ptr<Entity> e:m_world->getEntities())
    {
        if(std::shared_ptr<Animal> living = std::dynamic_pointer_cast<Animal>(e))
        {
            if(point.x()<e->getX()+e->getRadius() && point.x()>e->getX()-e->getRadius() &&
                    point.y()<e->getY()+e->getRadius() && point.y()>e->getY()-e->getRadius())
            {
                selectAnimal(living);
                return;
            }
        }
    }
    //if nothing found send nullptr
    selectAnimal(std::weak_ptr<Animal>());
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
