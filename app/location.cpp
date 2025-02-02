#include "location.hpp"
#include <cmath>
#include "simulator.hpp"

#define CLOSE_ENOUGH 0.05 // location less than this distance apart are considered the same.

Location::Location()
{
    x = arc4random_uniform(X_LIMIT);
    y = arc4random_uniform(Y_LIMIT);
}

Location::Location(double nx, double ny)
{
    x = nx;
    y = ny;
}

bool Location::move_toward(Location destination, double howfar)
{
    double dx = destination.x - x;
    double dy = destination.y - y;
    double theta = atan2(dy, dx);

    double distance = sqrt((dx * dx) + (dy * dy));

    // 4:04
    // prevents overshooting a point
    // stop at destination while moving towards it,
    // otherwise we could overshoot
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

// #define CLOSE_ENOUGH 0.05

// Location::Location() : x(arc4random_uniform(X_LIMIT)), y(arc4random_uniform(Y_LIMIT))
// {
// }

// Location::Location(double nx, double ny) : x(nx), y(ny)
// {
// }

// bool Location::move_forward(Location destination, double howFar)
// {
//     double dx = destination.x - x;
//     double dy = destination.y - y;
//     double theta = atan2(dy, dx);

//     double distance = sqrt(dx * dx + dy * dy);

//     if (distance < howFar)
//     {
//         x = destination.x;
//         y = destination.y;
//         return true;
//     }
//     else
//     {
//         x += (howFar * cos(theta));
//         y += (howFar * sin(theta));
//         return false;
//     }
// }

// double Location::get_distance(Location destination)
// {
//     double dx = destination.x - x;
//     double dy = destination.y - y;

//     double distance = sqrt(dx * dx + dy * dy);

//     return distance;
// }

// bool Location::at_location(Location destination)
// {
//     return (get_distance(destination) < CLOSE_ENOUGH);
// }

// double Location::get_x() { return x; }
// double Location::get_y() { return y; }
// void Location::set_x(double nx) { x = nx; }
// void Location::set_y(double ny) { y = ny; }