#pragma once

class Person;

class MobilityModel
{
protected:
    Person *person;

public:
    MobilityModel();
    void setPerson(Person *p);
    virtual void move() = 0;
};