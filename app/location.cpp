#include "location.hpp"
#include <cmath>
#include "simulator.hpp"
#include "random_generator.hpp"

#define CLOSE_ENOUGH 0.05

Location::Location()
{
    random_uniform my_gen;
    x = my_gen(X_LIMIT);
    y = my_gen(Y_LIMIT);
}

bool Location::move_toward(Location &destination, double howfar)
{
    double dx = destination.x - x;
    double dy = destination.y - y;
    double theta = std::atan2(dy, dx);

    double distance = std::sqrt((dx * dx) + (dy * dy));

    if (distance < howfar)
    {
        x = destination.x;
        y = destination.y;
        return true;
    }
    else
    {
        x += (howfar * std::cos(theta));
        y += (howfar * std::sin(theta));
        return false;
    }
}

double Location::get_distance(Location &other_location)
{
    double dx = other_location.x - x;
    double dy = other_location.y - y;
    return std::sqrt((dx * dx) + (dy * dy));
}

bool Location::at_location(Location &destination)
{
    return (get_distance(destination) < CLOSE_ENOUGH);
}

double Location::get_x() const { return x; }
double Location::get_y() const { return y; }
void Location::set_x(double nx) { x = nx; }
void Location::set_y(double ny) { y = ny; }