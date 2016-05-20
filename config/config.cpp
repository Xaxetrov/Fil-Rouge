#include "config.h"

// Threads
unsigned short config::NB_THREADS = 4;

// World
int config::WORLD_SIZE_X = 500;
int config::WORLD_SIZE_Y = 500;
unsigned short config::MIN_NUMBER_OF_ANIMAL = 10; //unused
unsigned short config::MIN_NUMBER_OF_HERBVORE = 10;
unsigned short config::MIN_NUMBER_OF_CARNIVORE = 10;
unsigned short config::MAX_NUMBER_HERBIVORE_CHAMPION = 10;
unsigned short config::MAX_NUMBER_CARNIVORE_CHAMPION = 0;

// Neurale network weight modification probability
double config::NN_WEIGHT_CHANGE_PROBABILITY = 0.1; // 10% chance of change by weight
double config::NN_WEIGHT_CHANGE_AVERAGE_VALUE = 0; // the average value added to a weight is 0
double config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION = 0.05; // the value added to a weight as a standart deviation of 0.05

// User Interface
unsigned int config::UPDATE_TIMER_INTERVALE = 2; //ms

// Resource evolution (proportional to the resource surface)
int config::EVOLUTION_WATER = 5;
int config::EVOLUTION_MEAT = -1;
int config::EVOLUTION_VEGETAL = 5;
unsigned int config::VEGETAL_MAXQUANTITY = 5000;
unsigned int config::WATER_MAXQUANTITY = 5000;

// Animal eating parameters
unsigned int config::EAT_MAX_VEGETAL_QUANTITY = 100; // the max is not the used value if hunger is 0
unsigned int config::EAT_MAX_MEAT_QUANTITY = 100; // the max is not the used value if hunger is 0
unsigned int config::EAT_MAX_HEALING_VALUE = 10; //the max is not the used value if life is full
unsigned int config::DRINK_MAX_VALUE = 100; // the max is not the used value if thrist is 0

// Animal Parameters
double config::INITIAL_RADIUS = 8;
double config::FATNESS_HERBIVORE = 0.0003; // the greater the constant is, the quicker the animals become fat...
double config::FATNESS_CARNIVORE = 0.0003;
double config::DEFAULT_ENERGY = 100;
double config::ENERGY_RECUP = 1;
double config::MOVE_ENERGY_LOSS = 0.5;
double config::TURN_ENERGY_LOSS = 50;
double config::MAX_SPEED_TO_EAT = 0.5;
unsigned int config::MAX_SPEED = 50;
int config::MAX_HEALTH = 5000;
unsigned int config::MAX_HUNGER = 2000;
unsigned int config::MAX_THIRST = 2000;
unsigned int config::MAX_SCORE = 1000;
int config::MAX_FEAR = 100;
unsigned int config::MAX_MATING = 2500;
unsigned int config::MAX_CHILD_PER_ANIMAL = 7;
unsigned int config::DEFAULT_HUNGER = 500;
unsigned int config::DEFAULT_THIRST = 500;
double config::MAX_ATTACK_ANGLE = PI/2; //attack angle is [-MAX_ATTACK_ANGLE ; MAX_ATTACK_ANGLE] //Disabled !
unsigned int config::ATTACK_ANIMAL = 100;
unsigned int config::ATTACK_HERBIVORE = 20;
unsigned int config::ATTACK_CARNIVORE = 200;
