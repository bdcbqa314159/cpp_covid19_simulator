#pragma once

class Person;

class MobilityModel
{
protected:
    Person *person = nullptr;

public:
    MobilityModel() = default;
    MobilityModel(Person *newPerson) : person(newPerson) {}
    void setPerson(Person *newPerson);
    virtual ~MobilityModel() = default;
    virtual void move() = 0;
};