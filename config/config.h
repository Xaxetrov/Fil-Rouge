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
   {-0.40, 0.40, 100}, /* numbers represent angle1, angle2 and range */
   {-1.5, -0.40, 70} ,
   {0.40, 1.5, 70}
};
const double VISIONSECTORS_NONLIVING[NB_VISIONSECTORS_NONLIVING][3] = {
   {-0.40, 0.40, 100}, /* numbers represent angle1, angle2 and range */
   {-1.5, -0.40, 70} ,
   {0.40, 1.5, 70}
};

// Neural network
const unsigned int NB_LAYERS = 2;
const unsigned int LAYER_SIZES[NB_LAYERS] = {NB_VISIONSECTORS_LIVING*2+NB_VISIONSECTORS_NONLIVING*2+3, 3};
// Neural network Entity id
const int NN_ID_ANIMAL = 2;
const int NN_ID_HERBIVORE = 1;
const int NN_ID_CARNIVORE = -1;
const int NN_ID_VEGETAL = 1;
const int NN_ID_WATER = -1;
const int NN_ID_MEAT = 0;
// Neurale network weight modification probability
const double NN_WEIGHT_CHANGE_PROBABILITY = 0.01; // 1% chance of change by weight
const double NN_WEIGHT_CHANGE_AVERAGE_VALUE = 0; // the average value added to a weight is 0
const double NN_WEIGHT_CHANGE_SDANTARD_DEVIATION = 0.1; // the value added to a weight as a standart deviation of 0.1

// User Interface
const unsigned UPDATE_TIMER_INTERVALE = 10; //ms

// Id
const unsigned int ID_ANIMAL = 20;
const unsigned int ID_HERBIVORE = 21;
const unsigned int ID_CARNIVORE = 22;
const unsigned int ID_RESOURCE = 10;
const unsigned int ID_WATER = 11;
const unsigned int ID_VEGETAL = 12;
const unsigned int ID_MEAT = 13;

// Resource evolution (proportional to the resource surface)
const int EVOLUTION_WATER = 10;
const int EVOLUTION_MEAT = -1;
const int EVOLUTION_VEGETAL = 10;

// Animal Parameters
const unsigned int MAX_HEALTH = 5000;
const unsigned int MAX_HUNGER = 1000;
const unsigned int MAX_THIRST = 1000;
const unsigned int MAX_FEAR = 100;
const unsigned int MAX_MATING = 1500;
const unsigned int MAX_CHILD_PER_ANIMAL = 6;
const unsigned int DEFAULT_HUNGER = 500;
const unsigned int DEFAULT_THIRST = 500;
const double MAX_ATTACK_ANGLE = PI/2; //attack angle is [-MAX_ATTACK_ANGLE ; MAX_ATTACK_ANGLE] //Disabled !
const unsigned int ATTACK_ANIMAL = 100;
const unsigned int ATTACK_HERBIVORE = 20;
const unsigned int ATTACK_CARNIVORE = 100;
// Animal eating parameters
const unsigned int EAT_MAX_VEGETAL_QUANTITY = 100; // the max is not the used value if hunger is 0
const unsigned int EAT_MAX_MEAT_QUANTITY = 100; // the max is not the used value if hunger is 0
const unsigned int EAT_MAX_HEALING_VALUE = 10; //the max is not the used value if life is full
// Animal drinking parameters
const unsigned int DRINK_MAX_VALUE = 100; // the max is not the used value if thrist is 0

#define FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
// World Parameters
const unsigned short MIN_NUMBER_OF_ANIMAL = 10; //unused
const unsigned short MIN_NUMBER_OF_HERBVORE = 15;
const unsigned short MIN_NUMBER_OF_CARNIVORE = 5;
const unsigned short MAX_NUMBER_HERBIVORE_CHAMPION = 10;
const unsigned short MAX_NUMBER_CARNIVORE_CHAMPION = 10;

#endif // CONFIG_H
