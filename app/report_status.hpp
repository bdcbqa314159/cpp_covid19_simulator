#pragma once
#include <iostream>
#include "simulator.hpp"

class report_status
{
public:
    int num_vulnerable{};
    int num_infected{};
    int num_immune{};
    int num_dead{};

    report_status() = default;
    report_status(int num_vulnerable, int num_infected, int num_immune, int num_dead) : num_vulnerable(num_vulnerable), num_infected(num_infected), num_immune(num_immune), num_dead(num_dead) {}

    friend std::ostream &operator<<(std::ostream &os, const report_status &obj)
    {
        double percent_dead = obj.num_dead * 100. / NUM_PEOPLE;
        os << obj.num_vulnerable << "\t" << obj.num_infected << "\t" << obj.num_immune << "\t" << obj.num_dead << "(" << percent_dead << "%)";
        return os;
    }
};