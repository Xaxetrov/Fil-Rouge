#include "WorldEditor.h"

#include "Water.h"
#include "Vegetal.h"
#include "Meat.h"

WorldEditor::WorldEditor(std::list<std::shared_ptr<Resource> > *resourcesList) :
    QGraphicsView(),
    resources(resourcesList)
{
    //setup default tools
    currantTool = Tools::water;
    currantRadius = 100;
    currantMaxQuantity = 4000;

    //setup a new scene
    m_scene = new QGraphicsScene();
    this->setScene(m_scene);

    //eneable map style navigation
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //disable scroll bar as counter intuitive
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void WorldEditor::updateScene()
{
    //clear the scene:
    m_scene->clear();
    m_scene->setSceneRect(0,0,m_world->getSizeX(),m_world->getSizeY());
    m_scene->setBackgroundBrush(QBrush(Qt::gray));
    m_scene->addRect(0,0,m_world->getSizeX(),m_world->getSizeY(),QPen(Qt::gray),colors.getBackgroundBrush());
    //add each entity to the scene one by one:
    for(std::shared_ptr<Resource> r : resources)
    {
        drawEntity(r);
    }
    emit sceneUpdated();
}

void WorldEditor::resizeEvent(QResizeEvent *e)
{
    this->fitInView(0,0,WORLD_SIZE_X,WORLD_SIZE_Y,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(e);
}

void WorldEditor::wheelEvent(QWheelEvent* e)
{
    QPoint numDegree = e->angleDelta() /8;
    qreal factor = std::pow(1.01, numDegree.ry());
    this->scale(factor, factor);
}
void WorldEditor::drawEntity(const std::shared_ptr<Entity> e)
{
    ///TODO implemente toric view on diagonals
   double x=e->getCoordinate().getX(), y=e->getCoordinate().getY();
   double radius = e->getRadius();
   std::vector<QPoint> positions;
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

void WorldEditor::drawBasicEntity(QPoint pos, double radius, QBrush brush, QPen pen)
{
    QRect baseSquare(pos.x()-radius,pos.y()-radius,2*radius,2*radius);
    m_scene->addEllipse(baseSquare,pen,brush);
}

void WorldEditor::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() != Qt::LeftButton && e->button() != Qt::RightButton)
        return;

    QPointF point = this->mapToScene(event->pos());

    if(e->button() == Qt::LeftButton)
    {
        addWithCurrantTool(point);
    }
    else if(e->button() == Qt::RightButton)
    {
        tryToRemoveAt(point);
    }
}


void WorldEditor::tryToRemoveAt(QpointF pos)
{
    for(auto resourcesIte = resources->begin() ; resourcesIte != resourcesIte.end() ; resourcesIte++ )
    {
        int radius = e->getRadius();
        if(pos.x()<e->getX()+radius && pos.x()>e->getX()-radius &&
                pos.y()<e->getY()+radius && pos.y()>e->getY()-radius)
        {
            resources->erase(resourcesIte);
            updateScene();
            return; // return when the first is found
        }
    }
}

void WorldEditor::addWithCurrantTool(QPointF pos)
{
    std::shared_ptr<Resource> toAdd;
    switch (currantTool) {
    case Tools::water:
        toAdd(std::make_shared<Water>(pos.x(),pos.y(),currantRadius,currantMaxQuantity));
        break;
    case Tools::vegetal:
        toAdd(std::make_shared<Vegetal>(pos.x(),pos.y(),currantRadius,currantMaxQuantity));
        break;
    case Tools::meat:
        toAdd(std::make_shared<Meat>(pos.x(),pos.y(),currantRadius,currantMaxQuantity));
        break;
    default:
        break;
    }
}
















