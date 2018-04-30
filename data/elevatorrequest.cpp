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
