#include "config.h"

// Threads
unsigned short config::NB_THREADS = 4;

// World
int config::WORLD_SIZE_X = 500;
int config::WORLD_SIZE_Y = 500;
unsigned short config::MIN_NUMBER_OF_HERBVORE = 10;
unsigned short config::MIN_NUMBER_OF_CARNIVORE = 0;
unsigned short config::MAX_NUMBER_HERBIVORE_CHAMPION = 10;
unsigned short config::MAX_NUMBER_CARNIVORE_CHAMPION = 10;
unsigned short config::PROBABILITY_TO_BE_CHILD_OF_CHAMPION = 90; //between 0 and 100

// Neurale network weight modification probability
double config::NN_WEIGHT_CHANGE_PROBABILITY = 0.005;
double config::NN_WEIGHT_CHANGE_AVERAGE_VALUE = 0; // the average value added to a weight is 0
double config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION = 0.01; // the value added to a weight as a standart deviation of 0.05

// User Interface
unsigned int config::UPDATE_TIMER_INTERVALE = 25; //ms
unsigned int config::FPS = 25; //ms

// Resource evolution (proportional to the resource surface)
double config::EVOLUTION_WATER = 1.0;
double config::EVOLUTION_MEAT = -0.7;
double config::EVOLUTION_VEGETAL = 0.4;
unsigned int config::VEGETAL_MAXQUANTITY = 500;
unsigned int config::WATER_MAXQUANTITY = 500;

// Animal eating parameters
unsigned int config::EAT_MAX_VEGETAL_QUANTITY = 100; // the max is not the used value if hunger is 0
unsigned int config::EAT_MAX_MEAT_QUANTITY = 100; // the max is not the used value if hunger is 0
unsigned int config::EAT_MAX_HEALING_VALUE = 10; //the max is not the used value if life is full
unsigned int config::DRINK_MAX_VALUE = 100; // the max is not the used value if thrist is 0

// Animal Parameters
double config::INITIAL_RADIUS = 7;
double config::FATNESS_HERBIVORE = 0.03; // the greater the constant is, the quicker the animals become fat...
double config::FATNESS_CARNIVORE = 0.03;
double config::DEFAULT_ENERGY = 100;
double config::ENERGY_RECUP = 1;
double config::MOVE_ENERGY_LOSS = 0.5;
double config::TURN_ENERGY_LOSS = 50;
double config::MAX_SPEED_TO_EAT = 0.3;
unsigned int config::MAX_SPEED = 50;
int config::MAX_HEALTH = 3000;
unsigned int config::MAX_HUNGER = 1800; // low value to have more fights :)
unsigned int config::MAX_THIRST = 3500;
unsigned int config::MAX_SCORE = 1000;
int config::MAX_FEAR = 100;
unsigned int config::MAX_MATING_HERBIVORE = 600;
unsigned int config::MAX_MATING_CARNIVORE = 900;
unsigned int config::MAX_CHILD_PER_ANIMAL = 5;
unsigned int config::DEFAULT_HUNGER = 500;
unsigned int config::DEFAULT_THIRST = 500;
double config::MAX_ATTACK_ANGLE = PI/2; //attack angle is [-MAX_ATTACK_ANGLE ; MAX_ATTACK_ANGLE] //Disabled !
unsigned int config::ATTACK_HERBIVORE = 0;
unsigned int config::ATTACK_CARNIVORE = 90;
