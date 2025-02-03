#include "mobility_model.hpp"
#include "person.hpp"

void MobilityModel::setPerson(Person *newPerson)
{
    if (newPerson != nullptr)
        person = newPerson;
}