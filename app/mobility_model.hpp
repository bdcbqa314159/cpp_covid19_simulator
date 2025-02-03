#pragma once

class Person;

class MobilityModel
{
protected:
    Person *person = nullptr;

public:
    MobilityModel() = default;
    void setPerson(Person *p);
    virtual void move() = 0;
};