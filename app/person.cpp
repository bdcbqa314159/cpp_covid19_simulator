#include "person.hpp"
#include "ppmodel.hpp"

Person::Person()
{
    PopularPlacesModel *model = new PopularPlacesModel();
    mobility_model = (MobilityModel *)model;
    mobility_model->setPerson(this);
    status = disease_status::VULNERABLE;
    disease_counter = INFECTION_TIME;
}

bool Person::infect()
{
    if (status == disease_status::VULNERABLE)
    {
        status = disease_status::INFECTED;
        return true;
    }
    else
        return false;
}

bool Person::try_infect(Person other_person)
{
    if (other_person.status != disease_status::INFECTED)
        return false;
    if (location.get_distance(other_person.location) > INFECTION_PROXIMITY)
        return false;
    if (try_event(INFECTION_PROBABILITY))
        return infect();
    return false;
}

void Person::progress_disease()
{
    if (status == disease_status::INFECTED)
    {
        disease_counter--;
        if (disease_counter <= 0)
        {
            double fatality_rate = NORMAL_FATALITY_RATE;
            if (saturated)
                fatality_rate = SATURED_FATALITY_RATE;
            if (try_event(fatality_rate))
                status = disease_status::DEAD;
            else
                status = disease_status::IMMUNE;
        }
    }
}

bool Person::is_alive()
{
    return status != disease_status::DEAD;
}