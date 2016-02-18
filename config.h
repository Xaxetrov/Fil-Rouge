#ifndef CONFIG_H
#define CONFIG_H

// General constants
const double PI = 3.1415926535897932;

// World
const int WORLD_SIZE_X = -1;
const int WORLD_SIZE_Y = -1;

// Vision
const int NB_VISIONSECTORS_LIVING = 3;
const int NB_VISIONSECTORS_NONLIVING = 3;

const int VISIONSECTORS_LIVING[NB_VISIONSECTORS_LIVING][3] = {
   {-15, 15, 100}, /* numbers represent angle1, angle2 and range */
   {-15, -30, 60} ,
   {15, 30, 60}
};
const int VISIONSECTORS_NONLIVING[NB_VISIONSECTORS_NONLIVING][3] = {
   {-15, 15, 100}, /* numbers represent angle1, angle2 and range */
   {-15, -30, 60} ,
   {15, 30, 60}
};

// Neural network
const unsigned int NB_LAYERS = 3;
const unsigned int LAYER_SIZES[NB_LAYERS] = {10, 6, 2};

#endif // CONFIG_H
