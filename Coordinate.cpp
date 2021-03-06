#include "Coordinate.h"
#include <cmath>
#include <algorithm>

#ifdef USE_INTEL_IPP
    #include <ipp.h>
    #include <ippvm.h>
#endif

Coordinate::Coordinate(double x, double y)
{
    set(x,y);
}

void Coordinate::set(double x, double y)
{
    m_polar_ready = false;

    int intX = (int) x;
    double fracX = x - intX;
    int intY = (int) y;
    double fracY = y - intY;

    m_x = (intX % config::WORLD_SIZE_X + config::WORLD_SIZE_X) % config::WORLD_SIZE_X + fracX; // x % y return a value btw -y + 1 and y - 1.
    m_y = (intY % config::WORLD_SIZE_Y + config::WORLD_SIZE_Y) % config::WORLD_SIZE_Y + fracY; // x % y + y return a value btw 1 and 2y - 1
                                                                       // (x % y + y) % y return a value btw 0 and y - 1
}

double Coordinate::getPolarAngle()
{
    if(!m_polar_ready)
    {
        updatePolar();
    }
    return m_a;
}

double Coordinate::getPolarRadius()
{
    if(!m_polar_ready)
    {
        updatePolar();
    }
    return m_r;
}

double Coordinate::getDistance(const Coordinate &c1, const Coordinate &c2)
{
    return sqrt(getDistanceCarre(c1, c2));
}

double Coordinate::getDistanceCarre(const Coordinate &c1, const Coordinate &c2)
{
    double deltaX = std::abs(c1.getX() - c2.getX());
    double deltaY = std::abs(c1.getY() - c2.getY());
    double deltaXTore = std::min(deltaX, config::WORLD_SIZE_X - deltaX);
    double deltaYTore = std::min(deltaY, config::WORLD_SIZE_Y - deltaY);
    return deltaXTore * deltaXTore + deltaYTore * deltaYTore;
}

double Coordinate::getAngle(const Coordinate &c1, const Coordinate &c2)
{
    double deltaX = c2.getX() - c1.getX();
    double deltaY = c2.getY() - c1.getY();

    if(deltaX > config::WORLD_SIZE_X/2.0)
    {
        deltaX += -config::WORLD_SIZE_X;
    }
    else if(deltaX < -config::WORLD_SIZE_X/2.0)
    {
        deltaX += config::WORLD_SIZE_X;
    }

    if(deltaY > config::WORLD_SIZE_Y/2.0)
    {
        deltaY += -config::WORLD_SIZE_Y;
    }
    else if(deltaY < -config::WORLD_SIZE_Y/2.0)
    {
        deltaY += config::WORLD_SIZE_Y;
    }
#ifndef USE_INTEL_IPP
    return std::atan2(deltaY,deltaX); //atan2 return value in [-pi;pi]
#else
    Ipp32f ippDeltaX = static_cast<Ipp32f>(deltaX);
    Ipp32f ippDeltaY = static_cast<Ipp32f>(deltaY);
    Ipp32f result;
    //use poor pressition IPP atan2 function for fast calculation
    //A11 garantee 11 bits corect (more than 3 decimal digit)
    //for beter presition A24 can be used (or if switched to 64f
    //up to A53) cf: intel doc ( https://software.intel.com/en-us/node/503292 )
    ippsAtan2_32f_A11(&ippDeltaY,&ippDeltaX,&result,1);
    return static_cast<double>(result);
#endif
/*
    double x1 = c1.getX();
    double x2 = c2.getX();
    double deltaX = x2 - x1;
    double y1 = c1.getY();
    double y2 = c2.getY();
    double deltaY = y2 - y1;
    double angle;

    if (std::abs(x1 - x2) > WORLD_SIZE_X)
    {
        deltaX += (x1 < x2) ? -WORLD_SIZE_X : WORLD_SIZE_X;
    }

    if (std::abs(y1 - y2) > WORLD_SIZE_Y)
    {
        deltaY += (y1 < y2) ? -WORLD_SIZE_Y : WORLD_SIZE_Y;
    }

    if (deltaX == 0)
    {
        angle = (y2 > y1) ? PI/2.0 : -PI/2.0;
    }
    else if (deltaX > 0)
    {
        angle = std::atan(deltaY / deltaX);
    }
    else
    {
        angle = std::atan(deltaY / deltaX) + PI;
    }

    return modulo2PI(angle);*/
}

double Coordinate::modulo2PI(double angle)
{
  while(angle >= PI)
  {
    angle -= 2*PI;
  }
  while(angle < -1 * PI)
  {
    angle += 2*PI;
  }
  return angle;
}

void Coordinate::updatePolar()
{
    m_r = std::hypot(m_x,m_y);
    m_a = std::atan2(m_y,m_x);
    m_polar_ready = true;
}
