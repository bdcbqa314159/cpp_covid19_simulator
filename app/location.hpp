#pragma once

class Location
{
private:
    double x{}, y{};

public:
    Location();
    Location(double nx, double ny) : x(nx), y(ny) {}

    double get_x() const;
    double get_y() const;
    void set_x(double nx);
    void set_y(double ny);

    double get_distance(Location &other_location);
    bool move_toward(Location &destination, double speed);
    bool at_location(Location &destination);
};