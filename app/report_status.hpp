#pragma once
#include <iostream>
#include "simulator.hpp"
#include "person.hpp"

class report_status
{
public:
    int num_vulnerable{}, num_infected{}, num_immune{}, num_dead{};

    report_status() = default;

    void operator()(Person &person)
    {
        if (!person.is_alive())
            num_dead++;
        if (person.status == disease_status::INFECTED)
            num_infected++;
        if (person.status == disease_status::IMMUNE)
            num_immune++;
        if (person.status == disease_status::VULNERABLE)
            num_vulnerable++;
    }

    friend std::ostream &operator<<(std::ostream &os, const report_status &obj)
    {
        double percent_dead = obj.num_dead * 100. / NUM_PEOPLE;
        os << obj.num_vulnerable << "\t" << obj.num_infected << "\t" << obj.num_immune << "\t" << obj.num_dead << "(" << percent_dead << "%)";
        return os;
    }
};