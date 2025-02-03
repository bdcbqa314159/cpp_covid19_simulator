#include "person.hpp"
#include "ppmodel.hpp"
#include "location.hpp"
#include "simulator.hpp"
#include "random_generator.hpp"
#include <cmath>

static Location popularPlaces[NUM_POPULAR_PLACES];

PopularPlacesModel::PopularPlacesModel() : MobilityModel()
{
    speed = -1;
    home = std::make_unique<Location>();
    if (try_event(DISTANCING_PROBABILITY))
        home_probability = DISTANCING_HOME_PROBABILITY; // I'm distancing
    else
        home_probability = NOT_DISTANCING_HOME_PROBABILITY; // I'm a COVIDiot
}

// why do I compare 'distance' with 'speed'? I have passed a 'speed' variable as a second argument to move_toward() in simulator.cpp.
void PopularPlacesModel::move()
{
    if (speed < 0)
    {
        person->location.set_x(home->get_x());
        person->location.set_y(home->get_y());
        pick_new_waypoint();
    }
    else if (person->location.at_location(*waypoint))
    {
        stay--;
        if (stay <= 0)
            pick_new_waypoint();
    }
    else
        person->location.move_toward(*waypoint, speed);
}

void PopularPlacesModel::pick_new_waypoint()
{
    random_uniform_int my_gen;
    speed = my_gen(PP_TOP_SPEED + 1);
    stay = my_gen(MAX_STAY);

    if (try_event(home_probability))
        waypoint = home.get();
    else
    {
        // pick a random popular place and go there
        int place = my_gen(NUM_POPULAR_PLACES);
        waypoint = &(popularPlaces[place]);
    }
}
