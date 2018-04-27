#include <random>

#include "person.h"
#include "../simulationmanager.h"

Person::Person()
{
    id = idCount++;

    targetFloor = rand() % SimulationManager::getInstance()->getAmountFloors() - 1;
    if (targetFloor > 0)
    {
        targetFloor++;
    }
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
