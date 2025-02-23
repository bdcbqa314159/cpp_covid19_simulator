#pragma once

#include <iostream>
#include "mobility_model.hpp"

constexpr size_t NUM_POPULAR_PLACES = 8;
constexpr size_t PP_TOP_SPEED = 20;
constexpr size_t MAX_STAY = 8;

constexpr double DISTANCING_PROBABILITY = 0.2;
constexpr double DISTANCING_HOME_PROBABILITY = 0.997;
constexpr double NOT_DISTANCING_HOME_PROBABILITY = 0.5;

class Location;

class PopularPlacesModel : public MobilityModel
{

private:
    Location *waypoint = nullptr;
    Location home;

    int speed{}, stay{};
    double home_probability{};

public:
    PopularPlacesModel();
    void pick_new_waypoint();
    virtual void move() override;
};
