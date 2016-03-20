#include <cmath>
#include <QWheelEvent>
#include <iostream>

#include "WorldWidget.h"
#include "Animal.h"
#include "Vegetal.h"
#include "Water.h"


WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
    //setup default selected animal
    selectedAnimal = weak_ptr<Animal>();

    //setup a new scene
    m_scene = new QGraphicsScene();
    this->setScene(m_scene);

    //eneable map style navigation
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //disable scroll bar as counter intuitive
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set timer:
    timer.setInterval(UPDATE_TIMER_INTERVALE);

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
    std::vector<shared_ptr<Entity>> & entities = m_world->getEntities();
    for(shared_ptr<Entity> ite : entities)
    {
        drawEntity(ite);
    }
    emit sceneUpdated();
}

void WorldWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(0,0,WORLD_SIZE_X,WORLD_SIZE_Y,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(e);
}

void WorldWidget::wheelEvent(QWheelEvent* e)
{
    QPoint numDegree = e->angleDelta() /8;
    qreal factor = std::pow(1.01, numDegree.ry());
    this->scale(factor, factor);
}

void WorldWidget::selectAnimal(weak_ptr<Animal> a)
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

void WorldWidget::drawEntity(const shared_ptr<Entity> e)
{
    ///TODO implemente toric view on diagonals
   double x=e->getCoordinate().getX(), y=e->getCoordinate().getY();
   int radius = e->getRadius();
   vector<QPoint> positions;
   positions.push_back(QPoint(x,y));
   if(x<radius)
   {
       positions.push_back(QPoint(x+WORLD_SIZE_X,y));
   }
   else if(x>WORLD_SIZE_X-radius)
   {
       positions.push_back(QPoint(x-WORLD_SIZE_X,y));
   }
   if(y<radius)
   {
       positions.push_back(QPoint(x,y+WORLD_SIZE_Y));
   }
   else if(y>WORLD_SIZE_Y-radius)
   {
       positions.push_back(QPoint(x,y-WORLD_SIZE_Y));
   }

   if(const shared_ptr<Animal> living = dynamic_pointer_cast<Animal>(e))
   {
       for(QPoint pos:positions)
       {
           drawAnimal(living,pos);
       }
   }
   else
   {
       for(QPoint pos:positions)
       {
           drawBasicEntity(pos,radius,colors.getEntityBrush(e),colors.getEntityPen(e));
       }
   }
}


void WorldWidget::drawAnimal(QPoint pos, int radius, double angle, QBrush brush, QPen pen)
{
    drawBasicEntity(pos,radius,brush,pen);
    //add an eye to show the looking direction
    int eyeRadius = radius/3;
    int eyeXCenter = pos.x()+cos(angle)*(radius-eyeRadius);
    int eyeYCenter = pos.y()+sin(angle)*(radius-eyeRadius);
    QRect eyeSquare(eyeXCenter-eyeRadius,eyeYCenter-eyeRadius,eyeRadius*2,eyeRadius*2);
    m_scene->addEllipse(eyeSquare,pen,colors.getTeamsEyeBrush());
}

void WorldWidget::drawAnimal(const shared_ptr<Animal> animal)
{
    QPoint pos(animal->getX(),animal->getY());
    drawAnimal(animal,pos);
}

void WorldWidget::drawAnimal(const shared_ptr<Animal> animal, QPoint pos)
{
    QPen animalPen;
    if(animal == selectedAnimal.lock())
        animalPen = colors.getTeamsSelectedPen();
    else
        animalPen = colors.getEntityPen(animal);
    drawAnimal(pos,animal->getRadius(),animal->getAngle(),colors.getEntityBrush(animal),animalPen);
}

void WorldWidget::drawBasicEntity(QPoint pos, int radius, QBrush brush, QPen pen)
{
    QRect baseSquare(pos.x()-radius,pos.y()-radius,2*radius,2*radius);
    m_scene->addEllipse(baseSquare,pen,brush);
}

void WorldWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    for(shared_ptr<Entity> e:m_world->getEntities())
    {
        if(shared_ptr<Animal> living = dynamic_pointer_cast<Animal>(e))
        {
            QPointF point = this->mapToScene(event->pos());
            if(point.x()<e->getX()+e->getRadius() && point.x()>e->getX()-e->getRadius() &&
                    point.y()<e->getY()+e->getRadius() && point.y()>e->getY()-e->getRadius())
            {
                selectAnimal(living);
                return;
            }
        }
    }
    //if nothing found send nullptr
    selectAnimal(weak_ptr<Animal>());
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
