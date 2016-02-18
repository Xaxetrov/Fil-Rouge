#include "WorldWidget.h"
#include "Animal.h"
#include "config.h"

WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
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
}

void WorldWidget::updateScene()
{
    //clear the scene:
    m_scene->clear();
    m_scene->setSceneRect(0,0,m_world->getSizeX(),m_world->getSizeY());
    m_scene->setBackgroundBrush(colors.getBackgroundBrush());
    //add each entity to the scene one by one:
    std::vector<Entity*> & entities = m_world->getEntities();
    for(Entity* ite : entities)
    {
        drawEntity(ite);
    }
}

void WorldWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(0,0,WORLD_SIZE_X,WORLD_SIZE_Y,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(e);
}

void WorldWidget::tick()
{
    ///TODO implemente tick on world
    //m_world->tick();
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
    //draw a circle representing the Entity
    QRect baseSquare(e->getX()-e->getRadius(),e->getY()-e->getRadius(),e->getRadius()*2,e->getRadius()*2);
    m_scene->addEllipse(baseSquare,colors.getEntityPen(e),colors.getEntityBrush(e));
    if(const Animal* const living = dynamic_cast<const Animal*>(e))
    {
        //add an eye to show the looking direction
        double angle = living->getAngle();
        int eyeRadius = e->getRadius()/3;
        int eyeXCenter = e->getX()+cos(angle)*(e->getRadius()-eyeRadius);
        int eyeYCenter = e->getY()+sin(angle)*(e->getRadius()-eyeRadius);
        QRect eyeSquare(eyeXCenter-eyeRadius,eyeYCenter-eyeRadius,eyeRadius*2,eyeRadius*2);
        m_scene->addEllipse(eyeSquare,colors.getEntityPen(e),colors.getTeamsEyeBrush());
    }
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}







