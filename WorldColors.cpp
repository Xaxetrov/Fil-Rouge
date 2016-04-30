#include "WorldColors.h"

#include <typeinfo>
#include "Animal.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Vegetal.h"
#include "Water.h"
#include "Meat.h"

WorldColors::WorldColors()
{
    backgroundBrush = QBrush(QColor(255,255,255));
    backgroundPen = QPen();
    waterBrush = QBrush(Qt::blue);
    waterPen = QPen(Qt::blue);
    grassBrush = QBrush(Qt::green);
    grassPen = QPen(Qt::green);
    meatBrush = QBrush(QColor(212,60,0));
    meatPen = QPen(QColor(212,60,0));

    // NNViewWidget
    connexionPen = QPen(Qt::gray);

    teamsPen = QPen(Qt::black);
    teamsSelectedPen = QPen(Qt::yellow);
    teamsEye = QBrush(Qt::black);
    teamsBrushs.push_back(QBrush(Qt::darkGreen));
    teamsBrushs.push_back(QBrush(Qt::red));
    teamsBrushs.push_back(QBrush(Qt::cyan));
    teamsBrushs.push_back(QBrush(Qt::yellow));
    teamsNullBrush = QBrush(Qt::gray);
    teamsNullPen = QPen(Qt::gray);
}


QBrush WorldColors::getEntityBrush(const std::shared_ptr<Entity> entity)
{
    int alpha = 255;
    if(auto r = std::dynamic_pointer_cast<Resource>(entity))
    {
        alpha = r->getQuantity()*255 / r->getMaxQuantity();
        if(alpha < 30)
            alpha = 30;
    }
    else if(auto a = std::dynamic_pointer_cast<Animal>(entity))
    {
        alpha = a->getHealth()*255 / MAX_HEALTH;
        if(alpha < 120)
            alpha = 120;
    }

    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(entity == nullptr)
    {
        return teamsNullBrush;
    }
    else if(typeid(*entity) == typeid( Animal ))
    {
        return setBrushAlpha(teamsBrushs.at(2), alpha);
    }
    else if(typeid(*entity) == typeid( Herbivore ))
    {
        return setBrushAlpha(teamsBrushs.at(0), alpha);
    }
    else if(typeid(*entity) == typeid( Carnivore ))
    {
        return setBrushAlpha(teamsBrushs.at(1), alpha);
    }
    else if(typeid(*entity) == typeid( Vegetal ))
    {
      return setBrushAlpha(grassBrush, alpha);
    }
    else if(typeid(*entity) == typeid( Water))
    {
      return setBrushAlpha(waterBrush, alpha);
    }
    else if(typeid(*entity) == typeid( Meat))
    {
      return setBrushAlpha(meatBrush, alpha);
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundBrush;
}

QBrush WorldColors::setBrushAlpha(QBrush brush, int alpha) const
{
    QColor color = brush.color();
    color.setAlpha(alpha);
    brush.setColor(color);
    return brush;
}

QPen WorldColors::setPenAlpha(QPen pen, int alpha) const
{
    QColor color = pen.color();
    color.setAlpha(alpha);
    pen.setColor(color);
    return pen;
}

QPen WorldColors::getEntityPen(const std::shared_ptr<Entity> entity)
{
    int alpha = 255;
    if(auto r = std::dynamic_pointer_cast<Resource>(entity))
    {
        alpha = r->getQuantity()*255 / r->getMaxQuantity();
        if(alpha < 30)
            alpha = 30;
    }
    else if(auto a = std::dynamic_pointer_cast<Animal>(entity))
    {
        alpha = a->getHealth()*255 / MAX_HEALTH;
        if(alpha < 120)
            alpha = 120;
    }

    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(entity == nullptr)
    {
        return teamsNullPen;
    }
    else if(typeid(*entity) == typeid( Animal ))
    {
        return setPenAlpha(teamsPen, alpha);
    }
    else if(typeid(*entity) == typeid( Herbivore ))
    {
        return setPenAlpha(teamsPen, alpha);
    }
    else if(typeid(*entity) == typeid( Carnivore ))
    {
        return setPenAlpha(teamsPen, alpha);
    }
    else if(typeid(*entity) == typeid( Vegetal ))
    {
      return setPenAlpha(grassPen, alpha);
    }
    else if(typeid(*entity) == typeid( Water ))
    {
      return setPenAlpha(waterPen, alpha);
    }
    else if(typeid(*entity) == typeid( Meat ))
    {
      return setPenAlpha(meatPen, alpha);
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundPen;
}

QBrush & WorldColors::getWaterBrush()
{
    return waterBrush;
}

QPen & WorldColors::getWaterPen()
{
    return waterPen;
}

QBrush & WorldColors::getGrassBrush()
{
    return grassBrush;
}

QPen & WorldColors::getGrassPen()
{
    return grassPen;
}

QPen & WorldColors::getConnexionPen()
{
    return connexionPen;
}

std::vector<QBrush> & WorldColors::getTeamsBrushs()
{
    return teamsBrushs;
}

QPen & WorldColors::getTeamsPen()
{
    return teamsPen;
}

QBrush & WorldColors::getBackgroundBrush()
{
    return backgroundBrush;
}

QBrush & WorldColors::getTeamsEyeBrush()
{
    return teamsEye;
}

QPen & WorldColors::getTeamsSelectedPen()
{
    return teamsSelectedPen;
}
