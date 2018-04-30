#ifndef ELEVATORREQUEST_H
#define ELEVATORREQUEST_H

#include "enum.h"
#include "data/person.h"

class ElevatorRequest
{
private:
    int startFloor;
    int endFloor;
    Person* person;

public:
    ElevatorRequest(int startFloor, int endFloor, Person* person)
        : startFloor(startFloor), endFloor(endFloor), person(person) {}

    int getStartFloor();
    int getEndFloor();
    Person* getPerson();
    Direction getDirection();
};

#endif // ELEVATORREQUEST_H
