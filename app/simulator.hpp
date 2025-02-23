#pragma once

constexpr size_t X_LIMIT = 5000, Y_LIMIT = 5000;
constexpr size_t SIM_HOURS = 5000, NUM_PEOPLE = 1000;
constexpr size_t INFECTION_TIME = 480;

constexpr double INFECTION_PROBABILITY = 0.4;
constexpr double NORMAL_FATALITY_RATE = 0.1;
constexpr double SATURED_FATALITY_RATE = 0.06;
constexpr double INFECTION_PROXIMITY = 5.;

constexpr size_t INITIAL_INFECTIONS = 30;
constexpr double SATURATION_THRESHOLD = NUM_PEOPLE / 5.;

constexpr size_t WINDOW_X = 500, WINDOW_Y = 500;

enum class disease_status
{
    VULNERABLE,
    INFECTED,
    IMMUNE,
    DEAD
};

extern bool saturated;

bool try_event(double probability);