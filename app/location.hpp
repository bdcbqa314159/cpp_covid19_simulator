#pragma once

class Location
{
private:
    double x, y;

public:
    Location();
    Location(double nx, double ny);

    double get_x();
    double get_y();
    void set_x(double nx);
    void set_y(double ny);

    double get_distance(Location other_location);
    bool move_toward(Location destination, double speed);
    bool at_location(Location destination);
};
// class Location
// {
// private:
//     double x{}, y{};

// public:
//     Location();
//     Location(double nx, double ny);

//     double get_x();
//     double get_y();
//     void set_x(double nx);
//     void set_y(double ny);

//     double get_distance(Location other_location);
//     bool move_forward(Location destination, double howFar);
//     bool at_location(Location destination);
// };