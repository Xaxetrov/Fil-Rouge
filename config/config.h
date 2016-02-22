#ifndef CONFIG_H
#define CONFIG_H

// General constants
const double PI = 3.1415926535897932;

// World
const int WORLD_SIZE_X = 500;
const int WORLD_SIZE_Y = 500;

// Vision
const int NB_VISIONSECTORS_LIVING = 3;
const int NB_VISIONSECTORS_NONLIVING = 3;

const double VISIONSECTORS_LIVING[NB_VISIONSECTORS_LIVING][3] = {
   {-0.26, 0.26, 100}, /* numbers represent angle1, angle2 and range */
   {-0.26, -0.79, 60} ,
   {0.26, 0.79, 60}
};
const double VISIONSECTORS_NONLIVING[NB_VISIONSECTORS_NONLIVING][3] = {
   {-0.26, 0.26, 100}, /* numbers represent angle1, angle2 and range */
   {-0.26, -0.79, 60} ,
   {0.26, 0.79, 60}
};

// Neural network
const unsigned int NB_LAYERS = 3;
const unsigned int LAYER_SIZES[NB_LAYERS] = {10, 6, 2};

// User Interface
const unsigned UPDATE_TIMER_INTERVALE = 100; //ms


#endif // CONFIG_H
