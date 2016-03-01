#include <cmath>
#include <QWheelEvent>

#include "WorldWidget.h"
#include "Animal.h"
#include "Vegetal.h"
#include "Water.h"


WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
    //setup default selected animal
    selectedAnimal = nullptr;

    //setup a new scene
    m_scene = new QGraphicsScene();
    this->setScene(m_scene);

    //eneable map style navigation
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //disable scroll bar as counter intuitive
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //fit the scene in the view
    //this->fitInView(0,0,WORLD_SIZE_X,WORLD_SIZE_Y,Qt::KeepAspectRatio);

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
    std::vector<Entity*> & entities = m_world->getEntities();
    for(Entity* ite : entities)
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

void WorldWidget::selectAnimal(Animal *a)
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

void WorldWidget::drawEntity(const Entity * e)
{
   if(const Animal* const living = dynamic_cast<const Animal*>(e))
   {
     //select the apropriate pen
     QPen animalPen;
     if(living == selectedAnimal)
         animalPen = colors.getTeamsSelectedPen();
     else
         animalPen = colors.getEntityPen(e);
     //draw a circle representing the Entity
     QRect baseSquare(e->getX()-e->getRadius(),e->getY()-e->getRadius(),e->getRadius()*2,e->getRadius()*2);
     m_scene->addEllipse(baseSquare,animalPen,colors.getEntityBrush(e));
     //add an eye to show the looking direction
     double angle = living->getAngle();
     int eyeRadius = e->getRadius()/3;
     int eyeXCenter = e->getX()+cos(angle)*(e->getRadius()-eyeRadius);
     int eyeYCenter = e->getY()+sin(angle)*(e->getRadius()-eyeRadius);
     QRect eyeSquare(eyeXCenter-eyeRadius,eyeYCenter-eyeRadius,eyeRadius*2,eyeRadius*2);
     m_scene->addEllipse(eyeSquare,animalPen,colors.getTeamsEyeBrush());
   }
   else
   {
     m_scene->addRect(e->getX(), e->getY(), e->getRadius(), e->getRadius(), colors.getEntityPen(e),colors.getEntityBrush(e));
   }
}

void WorldWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    for(Entity * e:m_world->getEntities())
    {
        if(Animal* living = dynamic_cast<Animal*>(e))
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
    selectAnimal(nullptr);
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
