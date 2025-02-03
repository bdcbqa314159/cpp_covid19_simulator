#pragma once

#include "mobility_model.hpp"

class Location;

#define NUM_POPULAR_PLACES 4

#define DISTANCING_PROBABILITY 0.2

#define DISTANCING_HOME_PROBABILITY 0.997
#define NOT_DISTANCING_HOME_PROBABILITY 0.5

#define PP_TOP_SPEED 20
#define MAX_STAY 8

class PopularPlacesModel : public MobilityModel
{

private:
    Location *waypoint;
    Location *home;
    int speed, stay;
    double home_probability;

public:
    PopularPlacesModel();
    void pick_new_waypoint();
    virtual void move() override;
};
