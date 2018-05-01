#include <QDebug>
#include <cmath>

#include "data/elevator/abstractelevator.h"
#include "singleton/simulationmanager.h"
#include "events/arrivalatfloorevent.h"

AbstractElevator::AbstractElevator(ElevatorList* elevatorList) : id(idCount++), elevatorList(elevatorList)
{
    Configuration* config = Configuration::getInstance();

    switch (config->getIdleScheduling())
    {
    case IdleScheduling::TOP:
        idleFloor = config->getAmountFloors() - 1;
        break;
    case IdleScheduling::BOTTOM:
        idleFloor = 0;
        break;
    default:
        qFatal("Unknown idle scheduling!");
        break;
    }

    floor = idleFloor;
}

int AbstractElevator::getId()
{
    return id;
}

int AbstractElevator::getNearestPassengerFloor()
{
    if (passengerList.empty())
    {
        return -1;
    }

    int nearestFloor = std::numeric_limits<int>::max();

    for (Person* person : passengerList)
    {
        if (std::abs(person->getTargetFloor() - floor) < std::abs(nearestFloor - floor))
        {
            nearestFloor = person->getTargetFloor();
        }
    }

    return nearestFloor;
}

void AbstractElevator::printEmbarkInfo(ElevatorRequest* request)
{
    qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", SimulationManager::getInstance()->getCurrentTime())
                                 << "] P" << QString().sprintf("%03d", request->getPerson()->getId())
                                 << " got into E" << id << " at F" << request->getStartFloor()
                                 << " (F" << request->getStartFloor() << " -> F" << request->getEndFloor() << ")";
}

int AbstractElevator::getCurrentFloor()
{
    return floor;
}

void AbstractElevator::setCurrentFloor(int floor)
{
    floor = floor;
}

bool AbstractElevator::isIdle()
{
    return idle;
}

void AbstractElevator::setIdle(bool idle)
{
    this->idle = idle;
}

std::list<Person*> AbstractElevator::disembark()
{
    std::list<Person*> passengersToDisembark;

    for (Person* person : passengerList)
    {
        if (person->getTargetFloor() == floor)
        {
            passengersToDisembark.push_back(person);
        }
    }

    for (Person* person : passengersToDisembark)
    {
        passengerList.remove(person);
    }

    return passengersToDisembark;
}
