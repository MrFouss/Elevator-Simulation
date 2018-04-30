#include <random>

#include "data/person.h"

#include "singleton/simulationmanager.h"

Person::Person()
{
    id = idCount++;

    do
    {
        targetFloor = rand() % Configuration::getInstance()->getAmountFloors();
    }
    while (targetFloor == 1);
}

int Person::getId()
{
    return id;
}

float Person::getTotalWaitTime()
{
    return totalWaitTime;
}

int Person::getCurrentFloor()
{
    return currentFloor;
}

void Person::setCurrentFloor(int floor)
{
    currentFloor = floor;
}

int Person::getTargetFloor()
{
    return targetFloor;
}

void Person::setTargetFloor(int floor)
{
    targetFloor = floor;
}

void Person::startWaitingElevator(float time)
{
    waitStartTime = time;
}

void Person::endWaitingElevator(float time)
{
    if (waitStartTime != -1.0)
    {
        totalWaitTime += (time - waitStartTime);
        waitStartTime = -1.0;
    }
}
