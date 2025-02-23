#pragma once

#include <iostream>
#include "simulator.hpp"
#include "mobility_model.hpp"
#include "location.hpp"

class MobilityModel;

class Person
{
public:
    Person();
    bool infect();
    bool try_infect(Person &other_person);
    void progress_disease();
    bool is_alive();

    Location location;
    std::unique_ptr<MobilityModel> mobility_model;
    disease_status status = disease_status::VULNERABLE;
    int disease_counter = INFECTION_TIME;
};