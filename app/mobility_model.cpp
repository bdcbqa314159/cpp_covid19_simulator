#include <cassert>
#include "mobility_model.hpp"
#include "person.hpp"

MobilityModel::MobilityModel()
{
    person = NULL;
}

void MobilityModel::setPerson(Person *p)
{
    assert(p != NULL);
    person = p;
}