#pragma once
#include <random>
#include "simulator.hpp"

class random_uniform
{
public:
    double operator()(double limit) const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> distribution(0, limit);

        return distribution(gen);
    }
};