#include "location.hpp"
#include <cmath>
#include "simulator.hpp"

#define CLOSE_ENOUGH 0.05

Location::Location()
{
    x = arc4random_uniform(X_LIMIT);
    y = arc4random_uniform(Y_LIMIT);
}

bool Location::move_toward(Location destination, double howfar)
{
    double dx = destination.x - x;
    double dy = destination.y - y;
    double theta = atan2(dy, dx);

    double distance = sqrt((dx * dx) + (dy * dy));

    if (distance < howfar)
    {
        x = destination.x;
        y = destination.y;
        return true;
    }
    else
    {
        x = x + (howfar * cos(theta));
        y = y + (howfar * sin(theta));
        return false;
    }
}

double Location::get_distance(Location other_location)
{
    double dx = other_location.x - x;
    double dy = other_location.y - y;
    return sqrt((dx * dx) + (dy * dy));
}

bool Location::at_location(Location destination)
{
    return (get_distance(destination) < CLOSE_ENOUGH);
}

double Location::get_x() { return x; }
double Location::get_y() { return y; }
void Location::set_x(double nx) { x = nx; }
void Location::set_y(double ny) { y = ny; }