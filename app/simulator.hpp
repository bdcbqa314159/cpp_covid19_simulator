#pragma once

#define X_LIMIT 5000
#define Y_LIMIT 5000

#define SIM_HOURS 5000
#define NUM_PEOPLE 1000

#define INFECTION_TIME 480

#define INFECTION_PROBABILITY 0.4

#define NORMAL_FATALITY_RATE 0.1
#define SATURED_FATALITY_RATE 0.06
#define INFECTION_PROXIMITY 5.0
#define INITIAL_INFECTIONS 30

#define SATURATION_THRESHOLD (NUM_PEOPLE / 5)

#define WINDOW_X 500
#define WINDOW_Y 500

enum class disease_status
{
    VULNERABLE,
    INFECTED,
    IMMUNE,
    DEAD
};

extern bool saturated;

bool try_event(double probability);