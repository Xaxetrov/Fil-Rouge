#ifndef WORLDCOLORS_H
#define WORLDCOLORS_H

#include <vector>
#include <QColor>
#include <QPen>

#include "Entity.h"

class WorldColors
{
public:
    WorldColors();

    QBrush & getEntityBrush(Entity entity);
    QPen & getEntityPen(Entity entity);

    QBrush & BackgroundBrush();
    QBrush & getWaterBrush();
    QPen & getWaterPen();
    QBrush & getGrassBrush();
    QPen & getGrassPen();
    std::vector<QBrush> & getTeamsBrushs();
    QPen & getTeamsPen();

private:
    ///environnement colors: (non living)
    //Background color:
    QBrush backgroundBrush;
    //water color:
    QBrush waterBrush;
    QPen waterPen;
    //grass color:
    QBrush grassBrush;
    QPen grassPen;
    ///living colors:
    //teams colors:
    std::vector<QBrush> teamsBrushs;
    QPen teamsPen;

};

#endif // WORLDCOLORS_H
