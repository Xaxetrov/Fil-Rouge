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

    QBrush & getBackgroundBrush();
    QBrush & getWaterBrush();
    QPen & getWaterPen();
    QBrush & getGrassBrush();
    QPen & getGrassPen();
    std::vector<QBrush> & getTeamsBrushs();
    QPen & getTeamsPen();
    QBrush & getTeamsEyeBrush();

private:
    ///environnement colors: (non living)
    //Background color:
    QBrush backgroundBrush;
    QPen backgroundPen; //used in not found case
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
    QBrush teamsEye;
};

#endif // WORLDCOLORS_H
