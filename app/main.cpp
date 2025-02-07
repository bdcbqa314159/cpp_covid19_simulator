#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <array>

#include "simulator.hpp"
#include "person.hpp"
#include "location.hpp"
#include "report_status.hpp"
#include "random_generator.hpp"

#define WINDOW_X 500
#define WINDOW_Y 500

class History_sfml
{
public:
    sf::Vector2f pos;
    sf::RectangleShape rectangle;

    History_sfml()
    {
        rectangle.setSize(sf::Vector2f(2, 2));
        rectangle.setFillColor(sf::Color::Black);
    }

    void setPos(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }

    void render(sf::RenderWindow &window)
    {
        rectangle.setPosition(pos);
        window.draw(rectangle);
    }

    void update(int x, int y, int total)
    {
        pos.x = WINDOW_X + (x * 1.0 / total) * (WINDOW_X);
        pos.y = WINDOW_Y - (y * 1.0 / NUM_PEOPLE) * (WINDOW_Y);

        if (y > SATURATION_THRESHOLD)
        {
            rectangle.setFillColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            rectangle.setFillColor(sf::Color(0, 0, 0, 255));
        }

        rectangle.setPosition(pos);
    }
};

class Person_sfml
{
public:
    sf::Vector2f pos;
    Person *person = nullptr;
    sf::CircleShape s;

    Person_sfml()
    {
        s.setFillColor(sf::Color::Black);
        s.setRadius(4);
    }

    void setPerson(Person *person)
    {
        this->person = person;
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(s);
    }

    void update()
    {
        pos.x = person->location.get_x() * WINDOW_X * 1.0 / X_LIMIT;
        pos.y = person->location.get_y() * WINDOW_Y * 1.0 / Y_LIMIT;

        s.setPosition(pos);

        switch (person->status)
        {
        case disease_status::DEAD:
            s.setFillColor(sf::Color(255, 0, 0, 255));
            break;
        case disease_status::VULNERABLE:
            s.setFillColor(sf::Color(0, 0, 0, 0.4 * 255));
            break;
        case disease_status::IMMUNE:
            s.setFillColor(sf::Color(0, 0, 255, 0.9 * 255));
            break;
        case disease_status::INFECTED:
            s.setFillColor(sf::Color(0, 0.7 * 255, 0, 0.9 * 255));
            break;
        }
    }
};

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

int main()
{

    Person people[NUM_PEOPLE];
    Person_sfml to_draw[NUM_PEOPLE];

    History_sfml hist_to_draw[SIM_HOURS];

    int infection_history[SIM_HOURS] = {0};

    // initial infections
    for (int i = 0; i < INITIAL_INFECTIONS; i++)
    {
        people[i].status = disease_status::INFECTED;
    }

    int max_infected_at_once = 0;

    for (int i = 0; i < NUM_PEOPLE; ++i)
    {
        to_draw[i].setPerson(&(people[i]));
        to_draw[i].update();
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_X * 2, WINDOW_Y), "covid19 simulation");
    window.setFramerateLimit(60);

    bool in = true;
    int i = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear(sf::Color::White);

        if (in && i < SIM_HOURS)
        {
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
                in = false;

            for (int j = 0; j < NUM_PEOPLE; ++j)
            {
                to_draw[j].update();
            }

            for (int j = 0; j < NUM_PEOPLE; ++j)
            {
                to_draw[j].render(window);
            }

            for (int j = 0; j < SIM_HOURS; j++)
            {
                hist_to_draw[j].update(j, infection_history[j], SIM_HOURS);
            }

            for (int j = 0; j < SIM_HOURS; j++)
            {
                hist_to_draw[j].render(window);
            }

            ++i;
        }

        else
        {
            for (int i = 0; i < NUM_PEOPLE; ++i)
            {
                to_draw[i].update();
            }

            for (int i = 0; i < NUM_PEOPLE; ++i)
            {
                to_draw[i].render(window);
            }

            for (int j = 0; j < SIM_HOURS; j++)
            {
                hist_to_draw[j].update(j, infection_history[j], SIM_HOURS);
            }

            for (int j = 0; j < SIM_HOURS; j++)
            {
                hist_to_draw[j].render(window);
            }
        }
        window.display();
    }

    std::cout << "Peak infections - " << max_infected_at_once << "\n";

    return 0;
}