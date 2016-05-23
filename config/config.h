#ifndef CONFIG_H
#define CONFIG_H

// General constants
const double PI =  3.1415926535897932;

// Neural network Entity id
const int NN_ID_ANIMAL = 2;
const int NN_ID_HERBIVORE = 1;
const int NN_ID_CARNIVORE = -1;
const int NN_ID_VEGETAL = 1;
const int NN_ID_WATER = -1;
const int NN_ID_MEAT = 0;

// Entities id
const unsigned int ID_ANIMAL = 20;
const unsigned int ID_HERBIVORE = 21;
const unsigned int ID_CARNIVORE = 22;
const unsigned int ID_RESOURCE = 10;
const unsigned int ID_WATER = 11;
const unsigned int ID_VEGETAL = 12;
const unsigned int ID_MEAT = 13;

// Vision
const int NB_VISIONSECTORS_LIVING = 3;
const int NB_VISIONSECTORS_NONLIVING = 3;
const int MAX_RANGE_OF_VISION = 100;
const double VISIONSECTORS_LIVING[NB_VISIONSECTORS_LIVING][3] = {
   {-0.40, 0.40, MAX_RANGE_OF_VISION}, /* numbers represent angle1, angle2 and range */
   {-1.5, -0.40, 0.7 * MAX_RANGE_OF_VISION} ,
   {0.40, 1.5, 0.7 * MAX_RANGE_OF_VISION}
};
const double VISIONSECTORS_NONLIVING[NB_VISIONSECTORS_NONLIVING][3] = {
   {-0.40, 0.40, MAX_RANGE_OF_VISION}, /* numbers represent angle1, angle2 and range */
   {-1.5, -0.40, 0.7 * MAX_RANGE_OF_VISION} ,
   {0.40, 1.5, 0.7 * MAX_RANGE_OF_VISION}
};

// Neural network
const unsigned int NB_LAYERS = 3;
const unsigned int LAYER_SIZES[NB_LAYERS] = {NB_VISIONSECTORS_LIVING*2+NB_VISIONSECTORS_NONLIVING*2+4, 12, 3};

// Reproduction
#define FEED_WORLD_WITH_CHILD_OF_CHAMPIONS

class config
{
public:

  // Threads
  static unsigned short NB_THREADS;

  // World
  static int WORLD_SIZE_X;
  static int WORLD_SIZE_Y;
  static unsigned short MIN_NUMBER_OF_ANIMAL; //unused
  static unsigned short MIN_NUMBER_OF_HERBVORE;
  static unsigned short MIN_NUMBER_OF_CARNIVORE;
  static unsigned short MAX_NUMBER_HERBIVORE_CHAMPION;
  static unsigned short MAX_NUMBER_CARNIVORE_CHAMPION;
  static unsigned short PROBABILITY_TO_BE_CHILD_OF_CHAMPION; //between 0 and 100

  // Neurale network weight modification probability
  static double NN_WEIGHT_CHANGE_PROBABILITY; // 10% chance of change by weight
  static double NN_WEIGHT_CHANGE_AVERAGE_VALUE; // the average value added to a weight is 0
  static double NN_WEIGHT_CHANGE_SDANTARD_DEVIATION; // the value added to a weight as a standart deviation of 0.05

  // User Interface
  static unsigned UPDATE_TIMER_INTERVALE; //ms

  // Resource evolution (proportional to the resource surface)
  static int EVOLUTION_WATER;
  static int EVOLUTION_MEAT;
  static int EVOLUTION_VEGETAL;
  static unsigned int VEGETAL_MAXQUANTITY;
  static unsigned int WATER_MAXQUANTITY;

  // Animal eating parameters
  static unsigned int EAT_MAX_VEGETAL_QUANTITY; // the max is not the used value if hunger is 0
  static unsigned int EAT_MAX_MEAT_QUANTITY; // the max is not the used value if hunger is 0
  static unsigned int EAT_MAX_HEALING_VALUE; //the max is not the used value if life is full
  static unsigned int DRINK_MAX_VALUE; // the max is not the used value if thrist is 0

  // Animal Parameters
  static double INITIAL_RADIUS;
  static double FATNESS_HERBIVORE; // the greater the staticant is, the quicker the animals become fat...
  static double FATNESS_CARNIVORE;
  static double FATNESS_ANIMAL;
  static double DEFAULT_ENERGY;
  static double ENERGY_RECUP;
  static double MOVE_ENERGY_LOSS;
  static double TURN_ENERGY_LOSS;
  static double MAX_SPEED_TO_EAT;
  static unsigned int MAX_SPEED;
  static int MAX_HEALTH;
  static unsigned int MAX_HUNGER;
  static unsigned int MAX_THIRST;
  static unsigned int MAX_SCORE;
  static int MAX_FEAR;
  static unsigned int MAX_MATING;
  static unsigned int MAX_CHILD_PER_ANIMAL;
  static unsigned int DEFAULT_HUNGER;
  static unsigned int DEFAULT_THIRST;
  static double MAX_ATTACK_ANGLE; //attack angle is [-MAX_ATTACK_ANGLE ; MAX_ATTACK_ANGLE] //Disabled !
  static unsigned int ATTACK_ANIMAL;
  static unsigned int ATTACK_HERBIVORE;
  static unsigned int ATTACK_CARNIVORE;

};

#endif // CONFIG_H
