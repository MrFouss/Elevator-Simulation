#include "elevatorrequest.h"

int ElevatorRequest::getStartFloor()
{
    return startFloor;
}

int ElevatorRequest::getEndFloor()
{
    return endFloor;
}

Person* ElevatorRequest::getPerson()
{
    return person;
}

Direction ElevatorRequest::getDirection()
{
    if (endFloor > startFloor)
    {
        return Direction::UP;
    }
    else
    {
        return Direction::DOWN;
    }
}
