#include <QDebug>
#include <cmath>

#include "elevator.h"
#include "simulationmanager.h"
#include "events/arrivalatfloorevent.h"

Elevator::Elevator(ElevatorList* elevatorList, Configuration config) : id(idCount++), elevatorList(elevatorList) {
    switch (config.getIdleScheduling())
    {
    case IdleScheduling::TOP:
        currentFloor = config.getAmountFloors() - 1;
        break;
    case IdleScheduling::BOTTOM:
        currentFloor = 0;
        break;
    default:
        qDebug().nospace().noquote() << "Unknown idle scheduling!";
        break;
    }
}

int Elevator::getId()
{
    return id;
}

int Elevator::getNearestPassengerFloor()
{
    if (passengerList.empty())
    {
        return -1;
    }

    int nearestFloor = std::numeric_limits<int>::max();

    for (Person* person : passengerList)
    {
        if (std::abs(person->getTargetFloor() - currentFloor) < std::abs(nearestFloor - currentFloor))
        {
            nearestFloor = person->getTargetFloor();
        }
    }

    return nearestFloor;
}

int Elevator::getCurrentFloor()
{
    return currentFloor;
}

void Elevator::setCurrentFloor(int floor)
{
    currentFloor = floor;
}

bool Elevator::isIdle()
{
    return idle;
}

void Elevator::setIdle(bool idle)
{
    this->idle = idle;
}

bool Elevator::isFloorInRightDirection(int floor)
{
    return (direction == Direction::UP && floor >= currentFloor)
            || (direction == Direction::DOWN && floor <= currentFloor);
}

std::list<Person*> Elevator::disembark()
{
    std::list<Person*> passengersToDisembark;

    for (Person* person : passengerList)
    {
        if (person->getTargetFloor() == currentFloor)
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

void Elevator::embark()
{
    std::list<ElevatorRequest*> requestList;

    switch (SimulationManager::getInstance()->getConfig().getBusyScheduling())
    {
    case BusyScheduling::SHORTEST_SEEK_TIME_FIRST:
        requestList = elevatorList->getRequestListAtFloor(currentFloor);
        break;

    case BusyScheduling::LINEAR_SCAN:
        requestList = elevatorList->getRequestListAtFloor(currentFloor, direction);
        break;

    default:
        qDebug().nospace().noquote() << "Unknown busy scheduling!";
        break;
    }

    for (ElevatorRequest* request : requestList)
    {
        passengerList.push_back(request->getPerson());
        qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", SimulationManager::getInstance()->getCurrentTime())
                                     << "] P" << QString().sprintf("%03d", request->getPerson()->getId())
                                     << " got into E" << id << " at F" << request->getStartFloor()
                                     << " (F" << request->getStartFloor() << " -> F" << request->getEndFloor() << ")";
        delete request;
    }
}

int Elevator::chooseFloor()
{
    SimulationManager* simulationManager = SimulationManager::getInstance();
    if (passengerList.empty())
    {
        if (elevatorList->isRequestAvailable())
        {
            switch (simulationManager->getConfig().getBusyScheduling())
            {
            case BusyScheduling::SHORTEST_SEEK_TIME_FIRST:
                return elevatorList->getNearestFloorWithRequest(currentFloor);

            case BusyScheduling::LINEAR_SCAN:
                if (elevatorList->areRequestAvailableInDirection(currentFloor, direction))
                {
                    return elevatorList->getNearestFloorWithRequest(currentFloor, direction);
                }
                else
                {
                    if (direction == Direction::UP)
                    {
                        direction = Direction::DOWN;
                    }
                    else if (direction == Direction::DOWN)
                    {
                        direction = Direction::UP;
                    }

                    embark();
                    return chooseFloor();
                }

            default:
                qDebug().nospace().noquote() << "Unknown busy scheduling!";
                return -1;
            }
        }
        else
        {
            switch (simulationManager->getConfig().getIdleScheduling())
            {
            case IdleScheduling::TOP:
                return simulationManager->getConfig().getAmountFloors() - 1;

            case IdleScheduling::BOTTOM:
                return 0;

            default:
                qDebug().nospace().noquote() << "Unknown idle scheduling!";
                return -1;
            }
        }
    }
    else
    {
        switch (simulationManager->getConfig().getBusyScheduling())
        {
        case BusyScheduling::SHORTEST_SEEK_TIME_FIRST:
            return getNearestPassengerFloor();

        case BusyScheduling::LINEAR_SCAN:
            return getNearestPassengerFloor();

        default:
            qDebug().nospace().noquote() << "Unknown busy scheduling!";
            return -1;
        }
    }
}
