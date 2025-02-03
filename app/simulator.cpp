#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <array>

#include "simulator.hpp"
#include "person.hpp"
#include "location.hpp"
#include "ui.hpp"
#include "report_status.hpp"
#include "random_generator.hpp"

bool saturated = false;
bool try_event(double probability)
{
    assert(probability >= 0.0 && probability <= 1.0);
    const int resolution = 100000;

    random_uniform my_gen;
    double rnum = my_gen(resolution);
    rnum /= resolution;
    return rnum <= probability;
}

int sim_main()
{
    // setup the simuation
    Person people[NUM_PEOPLE];

    // "flattening the curve"
    // this hitory array is the curve for stores the number
    // of current infections at each hour in the simulation
    int infection_history[SIM_HOURS];

    // zero out the history
    memset(infection_history, 0, sizeof(infection_history));
    // initial infections
    for (int i = 0; i < INITIAL_INFECTIONS; i++)
    {
        people[i].status = disease_status::INFECTED;
    }

    int max_infected_at_once = 0;

    for (int i = 0; i < SIM_HOURS; i++)
    {
        // redraw the UI, so you can see it happen
        if ((i % 2) == 0)
        {
            ui_redraw(people, NUM_PEOPLE, infection_history, SIM_HOURS);
        }

        // move people
        for (int p = 0; p < NUM_PEOPLE; p++)
        {
            if (people[p].is_alive())
            {
                people[p].mobility_model->move();
                people[p].progress_disease();
            }
        }

        // try to infect
        for (int p = 0; p < NUM_PEOPLE; p++)
        {
            if (people[p].is_alive())
            {
                for (int p2 = 0; p2 < NUM_PEOPLE; p2++)
                {
                    if (p != p2 && people[p2].is_alive())
                    {
                        people[p].try_infect(people[p2]);
                    }
                }
            }
        }

        // report status
        report_status my_report;
        for (int p = 0; p < NUM_PEOPLE; p++)
        {
            my_report(people[p]);
            if (my_report.num_infected > max_infected_at_once)
            {
                max_infected_at_once = my_report.num_infected;
            }
        }

        saturated = (my_report.num_infected > SATURATION_THRESHOLD);

        if ((i % 10) == 0 || my_report.num_infected == 0)
        {
            std::cout << my_report << "\n";
        }

        infection_history[i] = my_report.num_infected;

        if (my_report.num_infected == 0)
            break;
    }
    std::cout << "Peak infections - " << max_infected_at_once << "\n";
    return 0;
}

int main()
{
    return start_ui(sim_main);
    return 0;
}